
int main()
{  int n,b,w,a,s;
   n = 10;   b = w = a = s = 0;
      for(i = 0; i < n; i++) //L1
      {
          b = 2*i;
           for(j = i+1; j <= n; j++) //L2
           { 
            w = i+1+j; 
             for(k=0; k<=i; k=k+2) //L3
             w = i+1+k; a = w; 
        }
    } 
   for(i = 0; i <= b; i++) // L4 
    {
      t = s; 
       s = 3; 
    } 
    for(i = b; i >= 0; i--); // L5
 
	return 1;
}

/*<loopsfacts>
	 <loopId="5" maxcountAnyCalls=" 10" >
	 <loopId="4" maxcountAnyCalls=" 19" >
	 <loopId="3" maxcountAnyCalls=" 5" >
	 <loopId="2" maxcountAnyCalls=" 10" >
	 <loopId="1" maxcountAnyCalls=" 10" >
</loopsfacts>


<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<flowfacts>
    <function name="main" executed="true" extern="false">
        <loop loopId="1" line="5" source="pretraites/conf2.c" exact="true" maxcount="10" totalcount="10" maxexpr="partieEntiereInf((10-EPSILONINT-0)/1+1)" totalexpr="partieEntiereInf((10-EPSILONINT-0)/1+1)">
            <loop loopId="2" line="8" source="pretraites/conf2.c" exact="false" maxcount="10" totalcount="55" maxexpr="MAX(bIt-1,partieEntiereInf((10-EPSILON-0)/1+1)-1,partieEntiereInf((10-(0+1*(bIt-1-1+1)+1))/1+1))" totalexpr="SYGMA(bIt-1,partieEntiereInf((10-EPSILON-0)/1+1)-1,partieEntiereInf((10-(0+1*(bIt-1-1+1)+1))/1+1))">
                <loop loopId="3" line="11" source="pretraites/conf2.c" exact="false" maxcount="5" totalcount="275" maxexpr="MAX(bIt-1,partieEntiereInf((10-EPSILON-0)/1+1)-1,partieEntiereInf((0+1*(bIt-1-1+1)-0)/2+1))" totalexpr="SYGMA(bIt-1,partieEntiereInf((10-EPSILON-0)/1+1)-1,partieEntiereInf((10-(0+1*(bIt-1-1+1)+1))/1+1)*partieEntiereInf((0+1*(bIt-1-1+1)-0)/2+1))">
                </loop>
            </loop>
        </loop>
        <loop loopId="4" line="15" source="pretraites/conf2.c" exact="true" maxcount="19" totalcount="19" maxexpr="partieEntiereInf((2*(0+1*(9-1+1))-0)/1+1)" totalexpr="partieEntiereInf((2*(0+1*(9-1+1))-0)/1+1)">
        </loop>
        <loop loopId="5" line="20" source="pretraites/conf2.c" exact="true" maxcount="10" totalcount="10" maxexpr="partieEntiereInf((0-2*(0+1*(9-1+1)))/(-1+-1)+1)" totalexpr="partieEntiereInf((0-2*(0+1*(9-1+1)))/(-1+-1)+1)">
        </loop>
    </function>
</flowfacts>*/
