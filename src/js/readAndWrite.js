    var button = document.getElementById("btnAddressAdd");
	var processDuplicateButton = document.getElementById("processAllDup");
    var deleteNode = document.getElementById("delete");
	var noOfFields = 6;
	var inputString = "";
	var simTime="aaaa";
	
	/*alert('Javascript file is opened!');
	$(function() {
      alert('Jquery file is working');
	});*/
	
	function addSet(){
			var sourceNode = document.getElementById("external_plane_params");
			var node = duplicateNode(sourceNode, ["id", "name", "placeholder"]);
			//console.log(node);
			sourceNode.parentNode.appendChild(node);
			//console.log("Hello");
	}
	
	function deleteSet(){
			if(counter!=0)
			{
				var node = "external_plane_params_" + counter;
				var parent = document.getElementById(node);
				parent.parentNode.removeChild(parent);
				counter--;
				//if(counter<4) {document.getElementById("btnAddressAdd").disabled=false;}
				//console.log(parent);
				//var child = document.getElementById("college_"+counter);
				//child.parentNode.removeChild(child);
			}
    }
	
    
    function processAllSets () {
        //console.log("Yay");
		 //Sim Time
		simTime = parseFloat(document.getElementById("sim_time").value);
		
		//Weather set
		var stormMean = parseFloat(document.getElementById("storm_mean").value);
		var stormLow = parseFloat(document.getElementById("storm_length").value) + parseFloat(document.getElementById("storm_variation").value);
		var stormHigh = parseFloat(document.getElementById("storm_length").value) - parseFloat((document.getElementById("storm_variation").value));
		
		var weather = stormMean+" "+stormLow+" "+stormHigh;   
		
		// Airport set
		var berthNumber = document.getElementById("berth_number").value;
		var taxiwayNumber = document.getElementById("taxiway_number").value;
		var taxiwayTravelTime = document.getElementById("taxiway_travel_time").value;
		var deberthTime = 	document.getElementById("deberthing_time").value;
		
		var airportFeatures = berthNumber + " " + taxiwayNumber + " " + taxiwayTravelTime + " " + deberthTime;
		
	    //Regular plane
		var planeArrivalRate = parseFloat(document.getElementById("plane_arrival_rate").value);
		var planeArrivalLow = planeArrivalRate + parseFloat(document.getElementById("plane_arrival_rate_variation").value);
		var planeArrivalHigh = planeArrivalRate - parseFloat(document.getElementById("plane_arrival_rate_variation").value);
		
		var planeLoadingTime = parseFloat(document.getElementById("plane_loading_time").value);
		var loadingTimeLow = planeLoadingTime + parseFloat(document.getElementById("plane_loading_time_variation").value);
		var loadingTimeHigh = planeLoadingTime - parseFloat(document.getElementById("plane_loading_time_variation").value);
		
		var cat3 = document.getElementById("cat3_landing").value;
		
		var regularPlane = planeArrivalLow + " " + planeArrivalHigh + " " + loadingTimeLow + " " + loadingTimeHigh + " " + cat3;
		
		var field = "";
		var fieldValue="";
		var str="";
		var ex_str="";
		
		for (var i = 0; i <= counter; i++) 
		{
			for(var j=0; j < noOfFields; j++)
			{
				switch(j) 
				{
					case 0: field = "ex_plane_number"; break;
					case 1:	field = "ex_plane_rtt"; break;
					case 2: field = "ex_plane_rtt_variation";break;
					case 3: field = "ex_plane_loading_time";break;
					case 4: field = "ex_plane_loading_time_variation";break;
					case 5: field = "ex_cat3_landing";break;
					default: break;
				}
				if(i == 0)
				{
					fieldValue = document.getElementById(field);
					if(field == "ex_plane_rtt")
					{
						str+=(parseFloat(fieldValue.value) + parseFloat(document.getElementById("ex_plane_rtt_variation").value)) + " ";
						str+=(parseFloat(fieldValue.value) - parseFloat(document.getElementById("ex_plane_rtt_variation").value)) + " ";
						j+=1;
					}
					else if (field == "ex_plane_loading_time")
					{
					 str+=(parseFloat(fieldValue.value) + parseFloat(document.getElementById("ex_plane_loading_time_variation").value)) + " ";
					 str+=(parseFloat(fieldValue.value) - parseFloat(document.getElementById("ex_plane_loading_time_variation").value)) + " ";
					 j+=1;
					}
					else
					{
						str+=fieldValue.value+" ";
					}
				}
				else
				{
					fieldValue = document.getElementById(field+"_" + i);
					if(field == ("ex_plane_rtt_"+i))
					{
						str+=(parseFloat(fieldValue.value) + parseFloat(document.getElementById("ex_plane_rtt_variation_"+i).value))+" ";
						str+=(parseFloat(fieldValue.value) - parseFloat(document.getElementById("ex_plane_rtt_variation_"+i).value))+" ";
						j+=1;
					}
					else if(field == ("ex_plane_loading_time_"+i))
					{
						str+=(parseFloat(fieldValue.value) + parseFloat(document.getElementById("ex_plane_loading_time_variation_"+i).value))+" ";
						str+=(parseFloat(fieldValue.value) - parseFloat(document.getElementById("ex_plane_loading_time_variation_"+i).value))+" ";
						j+=1;
					}
					else
					{
						str+=fieldValue.value+" ";
					}
				}
				
			}  //end of inner for
			//console.log(str);
			ex_str += str + "\n";
			str="";
		} // end of outer for
		//console.log(ex_str);
		//console.log(simTime);
		var update_mode;
		if(document.getElementById("time").checked){update_mode="1"}
		else{update_mode="0"}

		inputString = simTime + "\n " + weather + "\n " + airportFeatures + "\n " + regularPlane + "\n " + (counter+1) + "\n" +ex_str 			+update_mode +"\n" + document.getElementById("updates").value;
		console.log(inputString);
		
			$.ajax({
      			type: "POST",
      			url: "php/save.php",
      			data: { input: inputString },
				success: function(msg) {
					console.log("msg" + msg);
				}
			});
			
			window.location.href = 'loading.html'; { input: inputString }
    }
    
    var counter = 0;
    function duplicateNode(/*DOMNode*/sourceNode, /*Array*/attributesToBump) {
        counter++;
        var out = sourceNode.cloneNode(true);
        if (out.hasAttribute("id")) { out["id"] = bump(out["id"]); }
        var nodes = out.getElementsByTagName("*");
        
        for (var i = 0, len1 = nodes.length; i < len1; i++) {
            var node = nodes[i];
			//console.log(node);
            for (var j = 0, len2 = attributesToBump.length; j < len2; j++) {
                var attribute = attributesToBump[j];
                if (node.hasAttribute(attribute)) {
                    node[attribute] = bump(node[attribute]);
                }
            }
        }
        
        function bump(/*String*/str) {
            return str + "_" + counter;
        }
      
        return out;
    }
	
	function checkInput(textid)
	{
		var input = document.getElementById(textid);
		var val = parseFloat(input.value);
		if(!input.value.match(/^\d+(\.\d+)?$/))
		{
			wrong(textid);
		}
		else
		{
		    if(textid == "berth_number" || textid == "taxiway_number" || textid == "ex_plane_number")
			{
				if(!input.value.match(/^\s*(\+|-)?\d+\s*$/) || val == 0){ wrong(textid); }
				else{correct(textid);}
			}
			else if(textid == "sim_time")
			{
				if(val > 87658.1 || val < 720){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "storm_mean")
			{
				if(val < 48 ){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "storm_length")
			{
				if(val > 24 || val < 2 ){wrong(textid);}
				else
				{
					correct(textid);
					if(val>=parseFloat(document.getElementById("storm_variation").value) && parseInt(document.getElementById("storm_variation").value)!=0) {correct("storm_variation");}
					else{wrong("storm_variation");}
				}
			}
			else if(textid == "storm_variation")
			{
				if(val>parseFloat(document.getElementById("storm_length").value)) {wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "taxiway_travel_time" || textid == "deberthing_time")
			{
				if(val == 0){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "plane_arrival_rate")
			{
				if(val == 0){wrong(textid);}
				else
				{
					correct(textid);
					if(val>=parseFloat(document.getElementById("plane_arrival_rate_variation").value)) {correct("plane_arrival_rate_variation");}
					else{wrong("plane_arrival_rate_variation");}
				}
			}
			else if(textid == "plane_arrival_rate_variation")
			{
				if(val>parseFloat(document.getElementById("plane_arrival_rate").value) && parseFloat(document.getElementById("plane_arrival_rate").value)!=0) {wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "plane_loading_time")
			{
				if(val == 0){wrong(textid);}
				else
				{
					correct(textid);
					if(val>=document.getElementById("plane_loading_time_variation").value){correct("plane_loading_time_variation");}
					else{wrong("plane_loading_time_variation");}
				}
			}
			else if(textid == "plane_loading_time_variation")
			{
				//console.log(val + "  >  " + document.getElementById("plane_loading_time").value);
				if(val>document.getElementById("plane_loading_time").value){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "cat3_landing")
			{
				if(val > 100 || val < 0){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid.indexOf("ex_plane_rtt") != -1)
			{
				if(textid.indexOf("variation") == -1)
				{
					var l =  textid.charAt(13);
					if(val==0){wrong(textid);}
					else{correct(textid);}
					if(l=="")
					{
						if(val>=document.getElementById("ex_plane_rtt_variation").value && document.getElementById("ex_plane_rtt_variation").value!=""){correct("ex_plane_rtt_variation");} else{wrong(("ex_plane_rtt_variation"))}
					}
					else
					{
						if(val>=document.getElementById("ex_plane_rtt_variation_"+l).value && document.getElementById("ex_plane_rtt_variation_"+l).value!=""){correct("ex_plane_rtt_variation_"+l);}
						else{wrong(("ex_plane_rtt_variation_"+l))}
					}
				}
				else
				{
					var l =  textid.charAt(23);
					if(l == "")
					{
						if(val>document.getElementById("ex_plane_rtt").value && document.getElementById("ex_plane_rtt").value!=0){wrong(textid);} 
						else{correct(textid);}
					}
					else
					{
						if(val>document.getElementById("ex_plane_rtt_"+l).value && document.getElementById("ex_plane_rtt_"+l).value!=0){wrong(textid);}
						else{correct(textid);}
					}
				}
			}
			else if(textid.indexOf("ex_plane_loading_time") != -1)
			{
				if(textid.indexOf("variation") == -1)
				{
					var l =  textid.charAt(22);
					if(val==0){wrong(textid);}
					else{correct(textid);}
					if(l=="")
					{
						if(val>=document.getElementById("ex_plane_loading_time_variation").value && document.getElementById("ex_plane_loading_time_variation").value!=""){correct("ex_plane_loading_time_variation");} else{wrong(("ex_plane_loading_time_variation"))}
					}
					else
					{
						if(val>=document.getElementById("ex_plane_loading_time_variation_"+l).value && document.getElementById("ex_plane_loading_time_variation_"+l).value!=""){correct("ex_plane_loading_time_variation_"+l);} else{wrong(("ex_plane_loading_time_variation_"+l))}
					}
				}
				else
				{
					var l =  textid.charAt(32);
					if(l == "")
					{
						if(val>document.getElementById("ex_plane_loading_time").value && document.getElementById("ex_plane_loading_time").value!=0){wrong(textid);} 
						else{correct(textid);}
					}
					else
					{
						if(val>document.getElementById("ex_plane_loading_time_"+l).value && document.getElementById("ex_plane_loading_time_"+l).value!=0){wrong(textid);} else{correct(textid);}
					}
				}
			}
			else if(textid == "ex_cat3_landing" || textid == "ex_cat3_landing_1" || textid == "ex_cat3_landing_2" || textid == "ex_cat3_landing_3" || textid == "ex_cat3_landing_4")
			{
				if(val > 100 || val < 0){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "updates")
			{
				if(document.getElementById("time").checked)
				{
					if(val==0){wrong(textid);}
					else{correct(textid);}
				}
				else
				{
					if(!input.value.match(/^\s*(\+|-)?\d+\s*$/) || val == 0){ wrong(textid); }
					else{correct(textid);}
				}
			}
			else{correct(textid);}
		}
	}

	function checkRadio(textid)
	{
		var input = document.getElementById("updates");
		var val = input.value;
		if(textid == "event")
		{
			if(!input.value.match(/^\s*(\+|-)?\d+\s*$/) || val == 0 || !input.value.match(/^\d+(\.\d+)?$/)){wrong("updates");}
			else{correct("updates");}
		}
		else if(textid == "time" && input.value!="")
		{
			if(val == 0 || !input.value.match(/^\d+(\.\d+)?$/)){wrong("updates");}
			else{correct("updates");}
		}
	}

	function correct(textid)
	{
		document.getElementById(textid).style.backgroundColor = "#BCED91";
		if(allCorrect())
		{
			document.getElementById("processAllDup").disabled = false;
		}
	}
	
	function wrong(textid)
	{
		if(document.getElementById(textid).value!="")
		{
			document.getElementById(textid).style.backgroundColor = "#FFCC00";
			//console.log(document.getElementById(textid).style.backgroundColor);
		}
		else
		{
			document.getElementById(textid).style.backgroundColor = "white";
		}
		document.getElementById("processAllDup").disabled = true;
	}

	function allCorrect()
	{
		var textbox = document.getElementsByTagName('input');
		var textid;
		var bgcolor = "rgb(255, 204, 0)";
		for(var i=0; i< textbox.length; i++)
		{	
			if(textbox[i].style.backgroundColor == bgcolor || textbox[i].style.backgroundColor == "white")
			{	
				return false;
			}
		}
		
		return true;
	}
