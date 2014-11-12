    var button = document.getElementById("btnAddressAdd");
	var processDuplicateButton = document.getElementById("processAllDup");
    var deleteNode = document.getElementById("delete");
	var noOfFields = 6;
	
	alert('Javascript file is opened!');
	$(function() {
      alert('Jquery file is working');
	}); 
	
	function addSet(){
		var sourceNode = document.getElementById("external_plane_params");
        var node = duplicateNode(sourceNode, ["id", "name", "placeholder"]);
        console.log(node);
        sourceNode.parentNode.appendChild(node);
		console.log("Hello");
	}	
	
	function deleteSet(){
        	var node = "external_plane_params_" + counter;
			var parent = document.getElementById(node);
			parent.parentNode.removeChild(parent);
			counter--;
			//console.log(parent);
			//var child = document.getElementById("college_"+counter);
			//child.parentNode.removeChild(child);
    }
	
    
    function processAllSets () {
        console.log("Yay");
		 //Sim Time
		var simTime = document.getElementById("sim_time"); 
		
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
		var ex_string="";
		
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
			console.log(str);
			ex_str = str + "\n";
			str="";
		} // end of outer for
		console.log(ex_str);
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
	
	
	
	$(document).ready(function(){     

		$('.save').click(function(e){ 

			var current_time = 123;
			var tasktitle = $("input#tasktitle").val();
			var dataString = 'current_time='+ current_time + '&tasktitle=' + tasktitle;
				
			$.ajax({
      			type: "POST",
      			url: "save.php",
      			data: dataString,
      				
      				success: function() {
      					$('.title').html("");
        				$('#message').html("✓ Logged!")
        				.hide()
       				 
       				 		.fadeIn(1500, function() {
         			 		$('#message').append("");
         			 		});
         				}
			});
			return false;

	    });
	});
	
	
	
	