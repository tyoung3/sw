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
break isaMatch
run tests/n3.sw
