#break swmain.c:40
#break Expand2
#break Expand3
#break FreeExpandedProcesseshttps://accounts.google.com/ServiceLogin?service=mail&continue=https://mail.google.com/mail/&hl=en
#break FreeLater
#run  tests/ae.sw 

#run /tmp/a.sw
#break visitS_tream
#run -m 2 tests/subnet1.sw
#run tests/sisub.sw
#run tests/lr.sw 
#run tests/ae.sw 
#run tests/aj2.sw 
#run tests/join.sw 
#run tests/asj.sw 
#run tests/aj.sw 
#break findAmatc#hingPort
##break swmain.c:43
#break autolink
#break createStream
#break visitHermt
#break createStream
#break ConfigError
#break FixComps
#break getStringVar
#break addStringVar
#break genPath
#run   <(echo '$X=xs;&U=tt;&T=x;(A a $_BROWSER  ) <- (&U T "1" $X $Y "4" );')
#run -m 3 <(echo 'A b; C d; (E)<-(F);')
#run -m 3 <(echo "A x.a;")
run te*/n6.sw
