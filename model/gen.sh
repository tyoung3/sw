# GEN.SH  -- Create StreamWork Network definition 


swfile="/tmp/gen.sw" 
gofile="/tmp/gen.go"

aa=5000

>$swfile
while [ $aa -gt 0 ] 
do	 
	echo "(A$aa)<-(B$aa);" >> $swfile
	aa=$(($aa-1));
done


#cat $swfile
sw  $swfile > $gofile 
#cat $gofile
swgraph $swfile
swgo $swfile
