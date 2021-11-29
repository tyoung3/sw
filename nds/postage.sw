# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

(getr   Rates "2021" ".17" "oz" ) 	-rate> 		 (cp ComputePostage);
(getld  GetLocDest "New York" "LA" )-locdest> 	1(cp);
(getws  GetWeight "10" "oz")  		-weight> 	2(cp);
(cp)3 								-postage> 	 (show Show);

