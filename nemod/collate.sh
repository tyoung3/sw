
# COLLATE.sh

	./sw */collate.sw
	[ -d /dev/shm/sw ] || mkdir /dev/shm/sw
	echo "(Sink strings.Print1)0 <- 0(Source strings.Gen1); " | ./sw > /dev/shm/sw/main.go
	
	cd /dev/shm/sw/
	go mod init collate/collate
	go run main.go 	
