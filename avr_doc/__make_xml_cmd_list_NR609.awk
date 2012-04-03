BEGIN { 
        FS   = ";" 
        cmd0 = ""
        comment0 = ""
        OFS  = "|"
        print "<commands>"
} 
{ 
    if ( $1 ~ /" -/ ) {
	        gsub("\"", "", $1)
	        split($1, a, "-")
	        gsub(" ", "", a[1])
	        cmd0 = a[1]
	        gsub(" Command", "", a[2])
	        sub(" ", "", a[2])
	        comment0 = a[2]
#	        print a[1],a[2];
  	        
    
    }
    else {
      if ( $3 ~ /Yes/ ) {  
	 if ( $1 ~ /QSTN/ ) {  
	    gsub("\"", "", $1)
	    gsub("&", "and", $2)
	    gsub("<", "", $2)
	    gsub(">", "", $2)
# 	    print cmd0,comment0,$1,$2,NR;
	    print "<command>"
	    print "<title>" comment0 "</title>"
	    print "<code>" cmd0 "</code>"
            print "<subcode>" $1 "</subcode>"
	    print "<means>" $2 "</means>"
	    print "</command>"
	 }   
      }
      else  next
    }
} 
END { 
     print "</commands>"
} 
