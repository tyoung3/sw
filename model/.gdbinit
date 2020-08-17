#break swmain.c:40
#break Expand2
#break Expand3
#break FreeExpandedProcesses
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
run tests/lr.sw 
