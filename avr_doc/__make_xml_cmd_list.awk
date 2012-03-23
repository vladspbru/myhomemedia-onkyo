BEGIN { 
        FS   = ";" 
        cmd0 = ""
        OFS  = "|"
        print "<commands>"
	print "<command>"
} 
{ 
    if ( $1 ~ /" -/ ) {
	        gsub("\"", "", $1)
	        split($1, a, "-")
	        gsub(" ", "", a[1])
	        cmd0 = a[1]
	        gsub(" Command", "", a[2])
	        sub(" ", "", a[2])
#	        print a[1],a[2];
	        print "</command>"
	        print "<command>"
	        print "<code>" a[1] "</code>"
	        print "<means>" a[2] "</means>"
  	        
    
    }
    else {
      if ( $3 ~ /Yes/ ) {  
	    gsub("\"", "", $1)
	    gsub("&", "and", $2)
#	    print cmd0,$1,$2,NR;
#            print "<subcode>" $1 "</subcode>"
#	    print "<means>" $2 "</means>"
    }
      else  next
    }
} 
END { 
     print "</command>"
     print "</commands>"
} 
