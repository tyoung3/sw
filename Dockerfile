FROM golang:1.14
LABEL ""Streamwork Demo""
WORKDIR /go/mod/sw
COPY  .  /go/mod/sw
RUN echo "deb http://ftp.us.debian.org/debian buster main" >>  /etc/apt/sources.list
RUN apt-get -y update
RUN apt-get -y upgrade	
RUN apt-get -y install gdb valgrind
RUN echo "set auto-load safe-path /" >> /root/.gdbinit
#RUN go install -v ./...

# Enable SSH:  No ssh server found in search
#RUN apt-cache search  sshd 
#RUN mkdir /var/run/sshd
#RUN echo 'root:JS86pb6QPEY' | chpasswd
#RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
# Fails: RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

#ENV NOTVISIBLE "in users profile"
#RUN echo "export VISIBLE=now" >> /etc/profile

#EXPOSE 22
# CMD ["sw"] # Sets initial commandRUN apt-get update && apt-get install -y openssh-server
