/** TODOs only


  These @todoS are sw general, not swproject specific: 
  High Priority:
  
    @todo Advertise StreamWork
    @todo fix null type path problem.
    @todo swgrapgh levels.
    @todo use $PATH and/or $GOPATH to find .sw and config files
    @todo Update project generation
	    @todo Send multiple(N option) IPs in go tests.
        @todo clean code
        @todo remove dead code
    @todo Todos to htdocs    
    @todo Fix defaultTypePath missing in config file.
    @todo env variable to pass return code?
    @todo create document tree to model component html file hierarchy
    @todo ? type conversion function
    @todo web server component library 
    @todo string/line channel type component library
    @todo math channel type component library [w/plotting -- geogebra?]
    @todo automate github search for components
        
    @todo Generate drawFBP format
        @todo Convert drawFBP format to SWL format
	    @todo Convert JPM's javaFBP NDs to SW NDs. https://jpaulm.github.io/fbp/jsyntax.htm
	Language changes:    
        @todo Make process parens optional
        @todo Inter-host stream sockets (IHSS component) and mocks.
	
    @todo Update fbp.twyoung.com web pages
	@todo Create Man pages w/Doxygen
 	@todo Create internal/html with module, package, function, and struct pages. Fix swgraph to find the pages.
 	@todo checkpoint restart
 	      IP save/restore; 
 	@todo Test on Windows
	
  Low Priority:	  
  @todo generate checksum from AST and comment in output. (? sepatate program?)   
    @todo Compare SWL files;  ala git diff 
	@todo Use PACKAGE_NAME { key: value} format for generated .yaml files.
	@todo Add tests for all useful sw modes.
	@todo Verify output from make check & make distcheck
	@todo Security check:
		Protection from buffer overflow (and other malicious input).
		Limited data lifetime (clearing buffers and heap data)
		Protection from ownership conflicts. 
	@todo Plugins:
		https://pkg.go.dev/plugin 
	@todo Process command/config arguments. 
	@todo negative nimports and noutports in swgen.sh to prioritize ports and reduce the number of goroutines.
	@todo Fix swgen arguments w/default generation. Generate in config file
 	@todo Graph .ISW files (prevent 'no processes' message.
 	@todo Implement Process name expansion. Ex. "_MONITOR;" launches system monitor
 	          
 DONE: 
	
    @done Set DEBUG=Y and add Debug(Notice) 
        @todo Generate channel type definitions and stringify
    @done component docs to README
    @done fix sw.twyoung.com
    @done default channel type path.  
    @done README TOC
	@done Synopsis to README.md.in
	@done Document environment variable usage.  DEBUG/USER/HOME
	@done Show full path for .sw and .cfg files in generated commentary. 
    @done Structure streams swgo.c [/usr/local/src/hw example code]
          Added typed channels.  
	@done Design Project logo and publish.
    @done fix logo graph if necessary
    @done fix 'swgraph n1.sw'
    @done Remove obsolete github branches
    @done remove log.Fatal from packages [ no more found ]
        panic or return/log error instead
	@done Make config an option in project generation.
	@done Make JPM's FBPgo (fbpGO?) Check feasability. 
	@done Discuss differences from 'classic' FBP.
		FBP inspired: 	http://www.jpaulmorrison.com/fbp/noflo.html
		Lifetime: 	https://suif.stanford.edu/collective/taint.html
			Q. Does Go clear buffers at close?
		Ownership: 	https://www.egnyte.com/resource-center/governance-guides/data-ownership
    @done Installation w/Autotools
	@done Add PREFIX statement to prefix process names with a string. 
	@done Make generated test_.go's  deadlock safe. Test w/collate.sw
	@done Improve module location.  Standardize on .../sw/MODULE/pkg/.... | Is .../sw
	@done  Restore poc test
	@done  Type names inside arrows(stream direction indicators). 
	@done  Document more functions 
	@done  Allow git.hub, etc. imports.  Simplify .sw file requirements.
	@done Structure in module/modele package.  Pass struct instead of integers.
	@done Avoid duplicates in YAML config file.
	@done If component involved in a cycle, then subtask all sends and receives
	@done Subtask channel send/receive when more than two ports,  for deadlock prevention.
	@done Fix swgo [poc]
	
 SHELVED:
	@shelved Wait on multiple inputs for example and deadlock prevention in ...test_.go files. -> or <- to diffferentiate.
	@shelved Generate Init function w/commentary
	@shelved Update .yaml file instead of replacing it.  Do not erase prev config.
	@shelved Blue/Gold code generation for deadlock prevention	
	@shelved output Buffer > 0  filtercode generation for deadlock prevention
 

Dumped:	
 	@dumped Generate project examples.
	    @dumped Fix swproject.sh/postage type error. [Works now]
        @dumped Make channels uni-directional [Makes no sense]
            
**/
 
