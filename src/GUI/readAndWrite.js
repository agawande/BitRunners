    var button = document.getElementById("btnAddressAdd");
	var processDuplicateButton = document.getElementById("processAllDup");
    var deleteNode = document.getElementById("delete");
	var noOfFields = 6;
	var inputString = "";
	var simTime="aaaa";
	
	alert('Javascript file is opened!');
	$(function() {
      alert('Jquery file is working');
	});
	
	function addSet(){
	    if(counter<5)
		{
			var sourceNode = document.getElementById("external_plane_params");
			var node = duplicateNode(sourceNode, ["id", "name", "placeholder"]);
			console.log(node);
			sourceNode.parentNode.appendChild(node);
			console.log("Hello");
			if(counter==4)
			{
				document.getElementById("btnAddressAdd").disabled=true;
			}
		}
	}
	
	function deleteSet(){
			if(counter!=0)
			{
				var node = "external_plane_params_" + counter;
				var parent = document.getElementById(node);
				parent.parentNode.removeChild(parent);
				counter--;
				if(counter<4) {document.getElementById("btnAddressAdd").disabled=false;}
				//console.log(parent);
				//var child = document.getElementById("college_"+counter);
				//child.parentNode.removeChild(child);
			}
    }
	
    
    function processAllSets () {
        console.log("Yay");
		 //Sim Time
		simTime = parseFloat(document.getElementById("sim_time").value);
		
		//Weather set
		var stormMean = 	parseFloat(document.getElementById("storm_mean").value);
		var stormLow = parseFloat(document.getElementById("storm_length").value) + parseFloat(document.getElementById("storm_variation").value)/2;
		var stormHigh = parseFloat(document.getElementById("storm_length").value) - parseFloat((document.getElementById("storm_variation").value)/2);
		
		var weather = stormMean+" "+stormLow+" "+stormHigh;   
		
		// Airport set
		var berthNumber = document.getElementById("berth_number").value;
		var taxiwayNumber = document.getElementById("taxiway_number").value;
		var taxiwayTravelTime = document.getElementById("taxiway_travel_time").value;
		var deberthTime = 	document.getElementById("deberthing_time").value;
		
		var airportFeatures = berthNumber + " " + taxiwayNumber + " " + taxiwayTravelTime + " " + deberthTime;
		
	    //Regular plane
		var planeArrivalRate = parseFloat(document.getElementById("plane_arrival_rate").value);
		var planeArrivalLow = planeArrivalRate + parseFloat(document.getElementById("plane_arrival_rate_variation").value)/2;
		var planeArrivalHigh = planeArrivalRate - parseFloat(document.getElementById("plane_arrival_rate_variation").value)/2;
		
		var planeLoadingTime = parseFloat(document.getElementById("plane_loading_time").value);
		var loadingTimeLow = planeLoadingTime + parseFloat(document.getElementById("plane_loading_time_variation").value)/2;
		var loadingTimeHigh = planeLoadingTime - parseFloat(document.getElementById("plane_loading_time_variation").value)/2;
		
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
				}
				else
				{
					fieldValue = document.getElementById(field+"_" + i);
				}	
				str+=fieldValue.value+" ";
			}  //end of inner for
			//console.log(str);
			ex_str += str + "\n";
			str="";
		} // end of outer for
		//console.log(ex_str);
		//console.log(simTime);
		inputString = simTime + "\n " + weather + "\n " + airportFeatures + "\n " + regularPlane + "\n " + ex_str;
		console.log(inputString);
		
			$.ajax({
      			type: "POST",
      			url: "save.php",
      			data: { input: inputString },
				success: function(msg) {
					console.log(msg);
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
				if(!input.value.match(/^\s*(\+|-)?\d+\s*$/)){ wrong(textid); }
				else{correct(textid);}
				if(textid == "berth_number" || textid == "taxiway_number" || textid == "ex_plane_number")
				{
					if(val == 0){wrong(textid);}
					else{correct(textid);}
				}
			}
			else if(textid == "sim_time")
			{
				console.log('rect');
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
				console.log(val + "     " + document.getElementById("storm_length").value);
				if(val>parseFloat(document.getElementById("storm_length").value)) {wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "taxiway_travel_time")
			{
				if(val == 0){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "deberthing_time")
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
					if(val>=parseFloat(document.getElementById("plane_arrival_rate_variation").value) && parseFloat(document.getElementById("plane_arrival_rate_variation").value)!=0) {correct("plane_arrival_rate_variation");}
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
					if(val>=document.getElementById("plane_loading_time_variation").value && document.getElementById("plane_loading_time_variation").value!=0){correct("plane_loading_time_variation");}
					else{wrong("plane_loading_time_variation");}
				}
			}
			else if(textid == "plane_loading_time_variation")
			{
				console.log(val + "  >  " + document.getElementById("plane_loading_time").value);
				if(val>document.getElementById("plane_loading_time").value){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "cat3_landing")
			{
				if(val > 100 || val < 0){wrong(textid);}
				else{correct(textid);}
			}
			else if(textid == "ex_plane_rtt" || textid == "ex_plane_rtt_1" || textid == "ex_plane_rtt_2" || textid == "ex_plane_rtt_3" || textid == "ex_plane_rtt_4")
			{
				if(val == 0){wrong(textid);}
				else
				{
					correct(textid);
					switch(textid)
					{
						case "ex_plane_rtt": if(val>=document.getElementById("ex_plane_rtt_variation").value && document.getElementById("ex_plane_rtt_variation").value!=0){correct("ex_plane_rtt_variation");} else{wrong(("ex_plane_rtt_variation"))} break;
						case "ex_plane_rtt_1": if(val>=document.getElementById("ex_plane_rtt_variation_1").value && document.getElementById("ex_plane_rtt_variation_1").value!=0){correct("ex_plane_rtt_variation_1");} else{wrong(("ex_plane_rtt_variation_1"))} break;
						case "ex_plane_rtt_2": if(val>=document.getElementById("ex_plane_rtt_variation_2").value && document.getElementById("ex_plane_rtt_variation_2").value!=0){correct("ex_plane_rtt_variation_2");} else{wrong(("ex_plane_rtt_variation_2"))} break;
						case "ex_plane_rtt_3": if(val>=document.getElementById("ex_plane_rtt_variation_3").value && document.getElementById("ex_plane_rtt_variation_3").value!=0){correct("ex_plane_rtt_variation_3");} else{wrong(("ex_plane_rtt_variation_3"))} break;
						case "ex_plane_rtt_4": if(val>=document.getElementById("ex_plane_rtt_variation_4").value && document.getElementById("ex_plane_rtt_variation_4").value!=0){correct("ex_plane_rtt_variation_4");} else{wrong(("ex_plane_rtt_variation_4"))} break;
						default: break;
					}
					
				}
			}
			else if(textid == "ex_plane_rtt_variation" || textid == "ex_plane_rtt_variation_1" || textid == "ex_plane_rtt_variation_2" || textid == "ex_plane_rtt_variation_3" || textid == "ex_plane_rtt_variation_4")
			{						
			    console.log(val > document.getElementById("ex_plane_rtt").value);
				switch(textid)
				{
						case "ex_plane_rtt_variation": if(val>document.getElementById("ex_plane_rtt").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_rtt_variation_1": if(val>document.getElementById("ex_plane_rtt_1").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_rtt_variation_2": if(val>document.getElementById("ex_plane_rtt_2").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_rtt_variation_3": if(val>document.getElementById("ex_plane_rtt_3").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_rtt_variation_4": if(val>document.getElementById("ex_plane_rtt_4").value){wrong(textid);} else{correct(textid);} break;
				}				
			}
			else if(textid == "ex_plane_loading_time" || textid == "ex_plane_loading_time_1" || textid == "ex_plane_loading_time_2" || textid == "ex_plane_loading_time_3" || textid == "ex_plane_loading_time_4")
			{
				if(val == 0){wrong(textid);}
				else
				{
					correct(textid);
					switch(textid)
					{
						case "ex_plane_loading_time": if(val>=document.getElementById("ex_plane_loading_time_variation").value && document.getElementById("ex_plane_loading_time_variation").value!=0){correct("ex_plane_loading_time_variation");}  else{wrong("ex_plane_loading_time_variation");} break;
						case "ex_plane_loading_time_1": if(val>=document.getElementById("ex_plane_loading_time_variation_1").value && document.getElementById("ex_plane_loading_time_variation_1").value!=0){correct("ex_plane_loading_time_variation_1");} else{wrong("ex_plane_loading_time_variation_1");} break;
						case "ex_plane_loading_time_2": if(val>=document.getElementById("ex_plane_loading_time_variation_2").value && document.getElementById("ex_plane_loading_time_variation_2").value!=0){correct("ex_plane_loading_time_variation_2");} else{wrong("ex_plane_loading_time_variation_2");} break;
						case "ex_plane_loading_time_3": if(val>=document.getElementById("ex_plane_loading_time_variation_3").value && document.getElementById("ex_plane_loading_time_variation_3").value!=0){correct("ex_plane_loading_time_variation_3");} else{wrong("ex_plane_loading_time_variation_3");} break;
						case "ex_plane_loading_time_4": if(val>=document.getElementById("ex_plane_loading_time_variation_4").value && document.getElementById("ex_plane_loading_time_variation_4").value!=0){correct("ex_plane_loading_time_variation_4");} else{wrong("ex_plane_loading_time_variation_4");} break;
					}
				}
			}
			else if(textid == "ex_plane_loading_time_variation" || textid == "ex_plane_loading_time_variation_1" || textid == "ex_plane_loading_time_variation_2" || textid == "ex_plane_loading_time_variation_3" || textid == "ex_plane_loading_time_variation_4")
			{
				switch(textid)
				{
						
						case "ex_plane_loading_time_variation": if(val>document.getElementById("ex_plane_loading_time").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_loading_time_variation_1": if(val>document.getElementById("ex_plane_loading_time_1").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_loading_time_variation_2": if(val>document.getElementById("ex_plane_loading_time_2").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_loading_time_variation_3": if(val>document.getElementById("ex_plane_loading_time_3").value){wrong(textid);} else{correct(textid);} break;
						case "ex_plane_loading_time_variation_4": if(val>document.getElementById("ex_plane_loading_time_4").value){wrong(textid);} else{correct(textid);} break;
				}
			}
			else if(textid == "ex_cat3_landing" || textid == "ex_cat3_landing_1" || textid == "ex_cat3_landing_2" || textid == "ex_cat3_landing_3" || textid == "ex_cat3_landing_4")
			{
				if(val > 100 || val < 0){wrong(textid);}
				else{correct(textid);}
			}
			else{correct(textid);}
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
			console.log(document.getElementById(textid).style.backgroundColor);
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
			if(textbox[i].value == 0 || textbox[i].style.backgroundColor == bgcolor || textbox[i].style.backgroundColor == "white")
			{	
				return false;
			}
		}
		
		return true;
	}