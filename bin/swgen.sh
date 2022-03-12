#!/bin/bash

Debug() {
        [ "$DEBUG" == "y" ] && echo -e "${yellow}$pgm/DEBUG: $* $reset" 
} 

init() {
    #pgm=swgen_none.sh
    pgm=`basename $0`
    version="0.0.0"
    HTML=fbpgo.html
    export modpath="$GOPATH/src"

             black="\u001b[30m"
               red="\u001b[31m"
             green="\u001b[32m"
            yellow="\u001b[33m"
              blue="\u001b[34m"
           magenta="\u001b[35m"
              cyan="\u001b[36m"
             white="\u001b[37m"
             reset="\u001b[0m"   
        lightgreen="\u001b[32;1m"

    Debug INIT: Running $pgm w/DEBUG.  Args: $*
    src=/usr/local/src
    [ -d $src ] || Die Cannot find directory $src

    lb='{'
    rb='}'
    for="for"
}


      
Die() {
                echo -e "$red$pgm/DIE: $* $reset"
                exit 1
}

IdSkel() {
        cat << EOF
        /*  Generated StreamWork component, $name, 
            by $pgm on `date` 
                $inp  input  ports 
                $outp output ports 
        */ 
EOF
}

GenOutP1() {
	Debug GenOutP1
	cat <<- EOF >> ${name}.go 
	$routine ${pfx}Send(cs[$outp], &wg2, arg, $outp)
EOF

}

GenInP1() {
	cat <<- EOF >> ${name}.go 
	$routine ${pfx}Recv(cs[$inp], &wg2, arg, $inp)
EOF

}
 
GenOutP() {      
         if [ $outp -eq 1 ]; then 
                cat << EOFX >> ${name}.go       
                
	 // $name: outp=$outp; inp=$inp; po=$po
                        cs[$inp] <- $inp
                        
EOFX
         else   
                
                $msg="$pkg/$name $((po-1))"
                cat << EOFX >> ${name}.go
                
                i := $po-1
                
                $for i >= $inp $lb
                        cs[i] <- "$msg" 
                        close(cs[i])
                        i--
                $rb

EOFX
        fi
}

makeYAML() {
    
	FAIL makeYAML $* 
        cat <<- EOF > $1
# $HOME/.sw/${pkg}.yaml
#    generated by swgen.sh `date`
---
global:                 # Options for all components in $pkg
  buffersize: 0         # Integer example.
  seqno: 1237          # Used to check for valid config file.
EOF
        
}

concatYAML() {
        Debug concatYAML $1 at `pwd`
        
        # yamllint <(( echo $module/${pkg}: ))
        cat <<- EOF >> $1
$module/${pkg}:
  bornon: `date -I'seconds'`
  title: "${cyan}Module:$module Pkg:$pkg${reset}"
  seqno: 1234   # Used to check for valid config file.
  buffersize: 1  # Integer example.
EOF
}

genPkgYAML() {  
        Debug genPkgYAML Args: $*
        

    args=" "
    getargs=""

    allargs=($*) 
	i=${#allargs[@]}  
        
    while [ $i -gt 1 ]; do 
        
	arg=${allargs[$(($i-2))]}
        val=${allargs[$(($i-1))]}
        
	Debug i=$i  arg=$arg val=$val
	
	getargs="$arg, _ := cfg.StringOr(\"$module/${pkg}.$arg\", \"$val\")
	$getargs" 
        
	args="fmt.Print(\"; $arg=\",$arg)  
	$args" 
	
	i=$(($i-2))
	
    done
     	
	Debug make args $*
}         

GenGo() {       
	 nports=$(($inps + $outps))
         Debug GenGo $name $* $config  $inps $outps  $nports $cfg_file
         #echo "$module/$pkg/${name}:" >> $cfg_file
	 
         cat << EOF > ${name}.go 
                package $pkg2
                
                `IdSkel` 
                 
                import (
                        _ "fmt"
                       "sync"
                       ${NULLIT}"github.com/$USER/$module"
                )
                
		// $name is @todo undocumented
            func $name(wg *sync.WaitGroup, arg []string, cs []chan interface{} ){
                
                defer wg.Done()
                $go_config3
EOF
	    
	 if [ $nports -gt 0 ]; then 
	    cat <<- EOFNP >> ${name}.go
	    var wg2 sync.WaitGroup
	    wg2.Add($nports) 

EOFNP
	 fi
	
	 if [ $nports -eq 1 ]; then
	 	routine=""
	 else 
	 	routine="go"
	 fi 
	 	
         outp=$nports
         inp=$inps
         while [ $outp -gt $inps ]; do
                outp=$(($outp - 1))
                GenOutP1
         done
         
         while [ $inp -gt  0 ]; do
                inp=$(($inp-1))
                GenInP1
         done
              
              
         if [ $nports -gt 0 ]; then 
        	 cat <<- EOF >> ${name}.go 
		 wg2.Wait()
           	 }
EOF
	 else 
	 	echo "}" >> ${name}.go
         fi  	 

        gofmt -w -s ${name}.go
	# GenConfig
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
                package $pkg2

	
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
        
Fail() {
	echo -e Usage: $pgm gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS Component [ARG VAL]...
	Die $*
}
        
makePkg2() {
	pkg2=`basename $pkg`
}
 
	# Find ROOT in ROOT/.../... 	
GetRoot() {
	p2=$1
		newPkg="`basename $p2`"
		pkgroot=$p2
		p2="`dirname $pkgroot`"
	while [ "$p2" != "." ]; do 
		pkgroot=$p2
		p2="`dirname $pkgroot`"
	done			
}
  
FixPkg() {
    Debug FixPkg
	dn="`basename $pkg`"  
	[ "$dn" == "$module" ] && pkg="`basename $pkg`" && NULLIT="// " || pfx="${module}."
	
	# Change pkg = $module/..../pkg2 to .../pkg2
        GetRoot $pkg
        Debug FixPkg: pkg=$pkg pkgroot=$pkgroot module=$module
        if [ "$module" != "$pkgroot" ]; then
        	foreign=1;  return
        fi 
        foreign=0	
}        
 
genConfigGO() {       	 	
       	 		cat <<- EOF > config.go
package $module

/* Generated by $pgm-$version */	      	 
import "sync"
import "fmt"
       	 		
type ipT struct {   /* Information Packet type */ 
	P string   /* Process Name  */
	S string   /* modulepath/component */
	I int      /* Port number */
}
			
	// Send transmits one IP   
	func  Send( ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int ) {
		defer wg2.Done()
		var ip ipT
		ip.I = nport
		ip.P = arg[0]
		ci   <- ip
	}	
	// Recv receives and reports one IP
	func  Recv( ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int ) {
		defer wg2.Done()
		ip, _ := <- ci   
		fmt.Println( arg[0], nport,  "received:", ip)
	}						 
EOF
}

#  Generate a skeleton component w/YAML   
GenYamlSkel() {
    config=$3
    Debug GenYamlSkel config=$config $*
	module=$1;shift;
        pkg=$1; 
        FixPkg
        if [ $foreign -eq 1 ]; then 
        	return
        fi  
        pkg=$newPkg
	Debug GenYamlSkel/FixPkg pfx=$pfx dn=$dn module=$module
        config=$2;  # NONE, TOML, YAML, other later maybe
        inp=$3
        outp=$4
        name=$5
        [ -z $inp ] && inp=0
        [ -z $outp ] && outp=0
        cfg_file="$src/$module/${module}.yaml"
        Debug GenYamlSkel-$version: $module $pkg config=$config input=$inp output=$outp NULLIT=$NULLIT PARAMS: $* 
        shift 5; Debug ARG/VAL: $*
        [ -z $module ] 	&& Fail Missing module
        [ -z $pkg ] 	&& Fail Missing package 
        [ -z $name ] 	&& Fail Missing name 
        mdl=$module
        [ "$module" == "$pkg" ] && mdl=".";  Debug mdl=$mdl pkg=$pkg
        [ -d $src/$mdl/$pkg ]       		 \
        	|| mkdir -p $src/$mdl/$pkg    \
        	|| Die Cannot create $src/$mdl/$pkg.
        src2=$src/$mdl/$pkg

    pushd $src/$module
                genPkgYAML   ; # ?? $*
        	Debug GenYamlSkel/GenConfig.go `pwd`

       	 	[ -f config.go ] ||   \
       	 		cat <<- EOF > config.go
package $module

/* Generated by swgen.sh-v$version */	      	 		
import config "github.com/zpatrick/go-config"
import "sync"
import "fmt"
       	 		
type ipT struct {   /* Information Packet type */ 
	P string   /* Process Name  */
	S string   /* modulepath/component */
	I int      /* Port number */
}
			
// PkgConfig initializes the go-config package.  See: https://github.com/zpatrick/go-config for details.
func PkgConfig()  *config.Config {
        mappings := map[string]string{
                "${pkg^^}_BUFFERSIZE": "${pkg}.buffersize",
        }
        
        return config.NewConfig([]config.Provider  {
                config.New${config}File("$src/${module}.yaml"), 
                config.NewEnvironment(mappings)} )      
}

	// Send transmits one IP   
	func  Send( ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int ) {
		defer wg2.Done()
		var ip ipT
		ip.I = nport
		ip.P = arg[0]
		ci   <- ip
	}	
	// Recv receives and reports one IP
	func  Recv( ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int ) {
		defer wg2.Done()
		ip, _ := <- ci   
		fmt.Println( arg[0], nport,  "received:", ip)
	}						 
EOF

    ### ??? swgen.sh gs n1 def YAML 1 0 Prt 


    pushd $src2 || Die Cannot cd  $src2
        Debug GenYamlSkel/subdir `pwd`
        cfg_file="$src/$module/${module}.yaml" 
        [ -f $cfg_file ] || makeYAML $cfg_file
        inps=$inp;outps=$outp
        	makePkg2
        	Debug `pwd` name: $name $inps $outps
        	[ -f ${name}.go ]       || GenGo     $inps $outps
        	[ -f ${name}_test.go ]  || GenTestGo $inps $outps
        Debug GenYamlSkel/Generate go.mod at $src/$mdl
        [ -f $src/$module/go.mod ] || (pushd $src/$module && go mod init ${modpath}/$module && popd) 
        go test -v ./...; # && $EDITOR ${name}_test.go ${name}.go
    popd        
}
       
#  Generate a skeleton component
GenSkel() {
    module=$1 ; 
    init $*;
    Debug GenSkel $*
    if [ "$3" == "YAML" ]; then 
        GenYamlSkel $*
        return
    fi    
	module=$1;shift
    pkg=$1; 
    FixPkg
    
    if [ $foreign -eq 1 ]; then 
       	return
    fi  
    
    pkg=$newPkg
	Debug GenSkel/FixPkg pfx=$pfx dn=$dn module=$module
    config=$2;  # NONE, TOML, YAML, other later maybe
    inp=$3
    outp=$4
    name=$5
    [ -z $inp ] && inp=0
    [ -z $outp ] && outp=0
    Debug GenSkel-$version: $module $pkg config=$config input=$inp output=$outp NULLIT=$NULLIT PARAMS: $* 
    shift 5; Debug ARG/VAL: $*
    [ -z $module ] 	&& Fail Missing module
    [ -z $pkg ] 	&& Fail Missing package 
    [ -z $name ] 	&& Fail Missing name 
    mdl=$module
    [ "$module" == "$pkg" ] && mdl=".";  Debug mdl=$mdl pkg=$pkg
    [ -d $src/$mdl/$pkg ]       		 \
        	|| mkdir -p $src/$mdl/$pkg    \
        	|| Die Cannot create $src/$mdl/$pkg.
    src2=$src/$mdl/$pkg

    pushd $src/$module
        	Debug GenSkel/GenConfig.go `pwd`

       	 	[ -f config.go ] || genConfigGO

     
    pushd $src2 || Die Cannot cd  $src2
        Debug GenSkel/subdir `pwd`
        cfg_file="$src/$module/${module}.yamlx" 
        inps=$inp;outps=$outp
        	makePkg2
        	Debug GenSkel/subdir2: `pwd` name: $name $inps $outps
        	[ -f ${name}.go ]       || GenGo     $inps $outps
        	[ -f ${name}_test.go ]  || GenTestGo $inps $outps
        Debug GenSkel/subdir3: Generate go.mod at $src/$mdl
        [ -f $src/$module/go.mod ] || (pushd $src/$module && go mod init ${modpath}/$module && popd) 
        go test -v ./...; # && $EDITOR ${name}_test.go ${name}.go
    popd        
}


CheckOut() {
        go get github.com/tyoung3/dummy_repository 
}

case $1 in  
        gs|skel)shift;GenSkel $*;;
        v)      echo $pgm-v$version;;
        x)  $EDITOR ${pgm}  &;;
        *)  cat <<- EOFX
        
        $0-v$version USAGE:  
                gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS COMPNAME [ARG VAL]...  . Generate skeleton components
                COMPNAME must begin with an upper case letter
                PKG and/or MODULE directories will be created if missing.
                CONFIG_TYPE can be NONE,TOML, or YAML
                v          . Display version
                x          . Edit $pgm
               --help      . Display this usage
                
                Example: $pgm gs ExMod pkg1  YAML 2 3 Func1 Func2 ... 
                
EOFX
        ;;
esac 
            
#################   END OF SCRIPT   ###################         


