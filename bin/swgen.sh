#!/bin/bash

# SWGEN.sh  Created from SWSKEL.sh from SW.sh
pgm=swgen.sh
version="0.3.0"
HTML=fbpgo.html

# NOTE: Go ignores files and directories beginning with '_', as in _OLD/

        black="\u001b[30m"
        red="\u001b[31m"
        green="\u001b[32m"
        lightgreen="\u001b[32;1m"
        yellow="\u001b[33m"
        blue="\u001b[34m"
        magenta="\u001b[35m"
        cyan="\u001b[36m"
        white="\u001b[37m"
        reset="\u001b[0m"
        
Die() {
                echo "$red$pgm/DIE: $*"
                exit 1
}

Debug() {
        [ "$DEBUG" == "y" ] && echo "$pgm/DEBUG: $* " 
}

Debug Running $pgm w/DEBUG

Verbose() {
        if [ ! -z $verbose ]; then
                echo "${pgm}.sh: $*"
        fi      
} 

# NotesFBP(): See SWSKEL.SH

Notesx() { 
        cat <<- EOF
                Workflow: https://gist.github.com/blackfalcon/8428401
                Code generation from BNF: https://github.com/goccmack/gocc
                Using gocc: https://medium.freecodecamp.org/write-a-compiler-in-go-quick-guide-30d2f33ac6e0
        Tutorial: https://tour.golang.org/welcome/1
        Specification: https://golang.org/ref/spec#Notation
                http://www.cs.sfu.ca/CourseCentral/383/tjd/     syntaxAndEBNF.html#defining-language-syntax-with-extended-backus-naur-form

EOF

}

src=~/go/mod

MakeDir2() {
        dir2=$1
        ddate=`date`
        Verbose Making $dir2
        [ -d $dir2 ]            \
        || ( mkdir -p $dir2             \
        && cat << EOF > $dir2/_README.md
        $dir2   generated by ${pgm}.sh-v$version on $ddate       
EOF
        )
}

MakeDir() {
        for dir in $*; do 
                MakeDir2 $dir
        done
}
        

# SeeDocs(): See SWSKEL.SH

IdSkel() {
        cat << EOF
        /*  Generated StreamWork component, $name, 
            by sw.sh on `date` 
                $inp  input  ports 
                $outp output ports 
        */ 
EOF
}

lb='{'
rb='}'
for="for"

GenOutP() {      
         if [ $outp -eq 1 ]; then 
                cat << EOFX >> ${name}.go       
                
	 // $name: outp=$outp; inp=$inp; po=$po
                        cs[$inp] <- $inp
                        
EOFX
         else   
                
                cat << EOFX >> ${name}.go
                
                i := $po-1
                
                $for i >= $inp $lb
                        cs[i] <- i+37
                        close(cs[i])
                        i--
                $rb

EOFX
        fi
}

makeFile() {
        red="\u001b[31m"
        reset="\u001b[0m"
        cat <<- EOF > $1
        # $HOME/.sw/${pkg}.toml generated by swskel `date` 
        [$pkg]   # Options for all components in package, $pkg
        seqno=1234    #Used to check for valid config file. 
        buffersize=1  #Integer example. 
        title="${red}StreamWork Example Package${reset}" 
        bornon=`date -I'seconds'
`
        
        # Add additional options here -- e.g.
        [bar]
        title="Foo.bar Example"
EOF
        
}


makeYAML() {
        red="\u001b[31m"
        reset="\u001b[0m"
        cat <<- EOF > $1
        # $HOME/.sw/${pkg}.yaml generated by swskel `date` 
        
        global:                 # Options for all components in $pkg
          buffersize: 1  	# Integer example. 
          seqno:      1234    	# Used to check for valid config file. 
EOF
        
}

concatYAML() {
        Debug concatYAML $1 at `pwd`
        cat <<- EOF >> $1
        $module/${pkg}:   
          bornon: `date -I'seconds'`
          title: "${lightgreen}Module:$module Pkg:$pkg${reset}" 
          seqno: 1234    #Used to check for valid config file. 
          buffersize: 1  #Integer example. 
        
EOF
        
}

genPkgConfig() {        fconfig="
/* PkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details*/
func PkgConfig()  *config.Config {
        mappings := map[string]string{
                \"${pkg^^}_BUFFERSIZE\": \"${pkg}.buffersize\",
        }
        
        return config.NewConfig([]config.Provider  {
                config.New${config}File(\"$GOPATH/mod/$module/$module.yaml\"), 
                config.NewEnvironment(mappings)} )      
}
"           
        go_config='config "github.com/zpatrick/go-config"'      
        go_config2="$fconfig"
        go_config3="cfg := PkgConfig(\"/home/tyoung3/go/mod/$module/${module}.toml\")
    bs, _ := cfg.IntOr(\"$module/${pkg}.buffersize\", 1)
    seqno, _ := cfg.IntOr(\"$module/${pkg}.seqno\", 1)
    title, _ := cfg.StringOr(\"$module/${pkg}.title\", \"n/a\")
    
    fmt.Println(title, 
                \"Running\", 
                arg[0], 
                version, 
                \"bs =\", bs, 
                \"seqno = \", seqno) 
    
    if seqno != 1234 {
        fmt.Println(
          \"Seqno not = 1234.  Missing config file?\")
    } 
    "    
}


genPkgYAML() {  
        Debug genPkgYAML
        
defversion='var version string="v0.0.0"'
fconfig="
/* PkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details*/
func PkgConfig()  *config.Config {
        mappings := map[string]string{
                \"BUFFERSIZE\": \"buffersize\",
                \"SEQNO\": \"seqno=7\",
        }
        
        return config.NewConfig([]config.Provider  {
                config.New${config}File(\"$cfg_file\"), 
                config.NewEnvironment(mappings)} )      
}
"           
        go_config='config "github.com/zpatrick/go-config"'      
        go_config2="$fconfig"
        go_config3="cfg := ${module}.PkgConfig()
    bs, _ := cfg.IntOr(\"$module/${pkg}.buffersize\", 1)
    seqno, _ := cfg.IntOr(\"$module/${pkg}.seqno\", 1)
    title, _ := cfg.StringOr(\"$module/${pkg}.title\", \"n/a\")
    
    fmt.Println(title, 
                \"Running\", 
                arg[0], 
                version, 
                \"bs =\", bs, 
                \"seqno = \", seqno) 
    
    if seqno != 1234 {
        fmt.Println(
          \"Seqno not = 1234.  Missing config file?\")
    } 
    "    
}       

noPkgConfig() {  
        Debug noPkgConfig $* $config
        go_config=""     
        go_config2=""
        go_config3="cfg := ${module}.PkgConfig() 
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
        fmt.Println(
                \"Running\", arg[0], version, \"bs =\", bs)  
        
    if seqno != 1234 {
        fmt.Println(
          \"Seqno not = 1234.  Missing config file?\")
    } "
}


noPkgYAML() {    
        Debug noPkgYAML $* $config
        go_config=""     
        go_config2=""
        go_config3="cfg := ${module}.PkgConfig() 
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
        fmt.Println(
                \"Running\", arg[0], version, 
                \"bs =\", bs, 
                \"seqno =\", seqno)  
        
    if seqno != 1234 {
        fmt.Println(
          \"Seqno not = 1234.  Missing config file?\")
    } "
}

GenConfig() {
	case $config in 
                 xxxTOML)  # Not Supported yet
                    cfg_file="$HOME/.sw/$pkg.toml" 
                    [ -f $cfg_file ] || makeFile $cfg_file      
                    [ ${pkg^^} == ${name^^} ]   \
                    && genPkgConfig                             \
                    || noPkgConfig 
                        ;;
                 YAML)
                        Debug GenConfig YAML 
                    concatYAML $cfg_file
                    if [ "$module" != "$pkg" ]; then 
                  	  go_config2=""
                    	go_config="\"$module/$module\""
                    fi	
                        ;;
                 *)go_config3="fmt.Println(
                \"Running\", arg[0])" 
                   ;;   
         esac
}         
         
        # See:  https://github.com/zpatrick/go-config
GenGo() {       
         Debug GenGo $name $* $config  
         
                 
         cat << EOF > ${name}.go 
                package $pkg
                
                `IdSkel` 
                 
                import (
                        "fmt"
                       "sync"
                       "$module/$module"
                )
                
                //  go_config2
                
            func $name(wg *sync.WaitGroup, arg []string, cs []chan interface{} ){
                $defversion
                
                defer wg.Done()
                $go_config3
EOF
              
              
        # For each output port, send one ip and close the port.
         
         if [ $outp -gt 0 ]; then  
                po=$(($outp+$inp))
                GenOutP
                outp=$(($outp-1))
         fi
         
         # For each input port, receive one ip.
         if [ $inp -gt  0 ]; then
                inp=$(($inp-1))
                pi=$inp
                cat << EOFZ >> ${name}.go  
                
                j := $inp
                $for j >=0 $lb
                        ip, ok := <-cs[j]
                        if ok != true {
                                break
                        }
                        fmt.Println(arg[0], "chan:", j, "IP:", ip)
                j--
            $rb   
EOFZ
         fi
              
               
         cat << EOF >> ${name}.go 
            }
EOF

        gofmt -w -s ${name}.go
        echo Debug: $EDITOR $cfg_file
	GenConfig
        # $EDITOR $cfg_file &
}

GenTestOutP() {         
                cat << EOFX >> ${name}_test.go
                
                i := $ni
                $for i >= 0 $lb
                        cs[i] <- i
                        close(cs[i])
                        i--
                $rb
EOFX
}

GenTestGo() {   
         ni=$1
         no=$2
	 Debug GenTestGo $name $ni $no
	 inp=$ni; outp=$no
         cat << EOFY > ${name}_test.go
                package $pkg

	
        `IdSkel`
        
import "testing"
import "fmt"
import "sync"

func TestSkel_${name}(t *testing.T) {
        var cs  []chan interface{}
        var wg  sync.WaitGroup
        
        arg := []string{"TestSkel_${name}"}
        
        fmt.Println(arg[0])
EOFY
   
    nports=$(($no + $ni))
    if [ $nports -gt 0 ]; then      
                cat << EOFY >> ${name}_test.go  
                $for i :=0; i < $no + $ni; i++ $lb
                        cs = append(cs,make(chan interface{}))
                $rb
EOFY
        fi
        
         cat << EOFY >> ${name}_test.go
        
        wg.Add(2) 
        go func() { 
EOFY
                        # For each input port, receive one ip.
         if [ $no -gt  0 ]; then
                no=$(($no-1))
                po=$(($no+$ni))
                cat << EOFZ >> ${name}_test.go  
 
                j := $po
                $for j >= $ni $lb
                        ip, ok := <- cs[j]
                        if ok != true {
                                break
                        }
                        fmt.Println("chan:",j,"IP:",ip);
                j--
            $rb   
              
EOFZ
         fi
     
     if [ $ni -gt 0 ];  then
        ni=$(($ni-1))
        #echo ni=$ni
                GenTestOutP
         fi
         
         cat << EOFY >> ${name}_test.go
                        fmt.Println("TestSkel_${name} Ended")
                        wg.Done()
                        return
        }() 
        
        go $name(&wg, arg,  cs)
        wg.Wait()       

}
        
EOFY
	#go mod init $pkg 
        go fmt ${name}_test.go
}
        
#  Generate a skeleton component
GenSkel() {
	module=$1;shift;
        pkg=$1; 
        config=$2;  # NONE, TOML, YAML, other later maybe
        inp=$3
        outp=$4
        name=$5
        [ -z $inp ] && inp=0
        [ -z $outp ] && outp=0
        cfg_file="$GOPATH/mod/$module/$module.yaml"
        Debug GenSkel: $module $pkg config=$config input=$inp output=$outp $*
        shift 4
        [ -z $module ] 	&& Die  Usage: $pgm gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS
        [ -z $pkg ] 	&& Die  Usage: $pgm gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS
        [ -z $name ] 	&& Die  Usage: $pgm gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS
        mdl=$module
        [ "$module" == "$pkg" ] && mdl=".";  Debug mdl=$mdl pkg=$pkg
        [ -d $src/$mdl/$pkg ]       		 \
        	|| mkdir -p $src/$mdl/$pkg    \
        	|| Die Cannot create $src/$mdl/$pkg.
        src2=$src/$mdl/$pkg
        pushd $src/$module
        genPkgYAML  
        	Debug GenSkel/GenConfig.go `pwd`
       	 	[ -f config.go ] 								\
       	 		|| ( 									\
       	 		   echo package $module >> config.go&& echo 				\
       	 		&& echo import config \"github.com/zpatrick/go-config\">> config.go	\
       	 		&& echo "$fconfig" >> config.go )   
        popd
        pushd $src2 || Die Cannot cd  $src2
        Debug GenSkel/subdir `pwd`
        cfg_file="$GOPATH/mod/$module/${module}.yaml" 
        [ -f $cfg_file ] || makeYAML $cfg_file
        inps=$inp;outps=$outp
        for name in $*; do 
        	Debug `pwd` name: $name $inps $outps
        	[ -f ${name}.go ]       || GenGo     $inps $outps
        	[ -f ${name}_test.go ]  || GenTestGo $inps $outps
        done
        Debug Generate go.mod at $src/$mdl
        [ -f $src/$module/go.mod ] || (pushd $src/$module && go mod init $module/$module && popd) 
        go test -v ./...; # && $EDITOR ${name}_test.go ${name}.go
        
}


CheckOut() {
        go get github.com/tyoung3/dummy_repository 
}

pgm=`basename $0`
case  $pgm in 
        swskel|skel)GenSkel $* && exit 0 || Die $* failed.;;
esac
        
case $1 in      
        gs|skel)shift;GenSkel $*;;
        v)      echo $pgm-v$version;;
        x)  $EDITOR ${pgm}  &;;
        *)  cat <<- EOFX
        
        $0-v$version USAGE:  
                gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS COMPNAME... 	. Generate skeleton components
                                        COMPNAME must begin with an upper case letter
                                        PKG and/or MODULE directories will be created if missing.
                                        CONFIG_TYPE can be NONE,TOML, or YAML
                v                       					. Display version
                x                       					. Edit $pgm
               --help                  						. Display this usage
                
                Example: $pgm gs ExMod pkg1  YAML 2 3 Func1 Func2 ... 
                
EOFX
#  Removed 7/23/2020            r                       . Run fbpgo.go
        ;;

esac    
            
#################   END OF SCRIPT   ###################         


