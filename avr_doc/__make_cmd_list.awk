BEGIN { 
        FS   = ";" 
        cmd0 = ""
        OFS  = "|"
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
    }
    else {
      if ( $3 ~ /Yes/ ) {  
	    gsub("\"", "", $1)
	    print cmd0,$1,$2,NR;
      }
      else  next
    }
} 
