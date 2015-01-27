
sock.on("disconnect", function(client){});

$(document).ready(function(){
	myname = localStorage.getItem("myname");
	if(myname == null){
		setname = prompt("初めての方ですね。\nお名前を入力してください。\n");
		localStorage.setItem("myname",setname);
		alert(setname + "さん、こんにちは！");
		myname = setname;
		sock.emit("newname",{value: myname});
		sock.emit("myname", {value: myname});
		document.getElementById("myname").innerHTML = myname;
	}else{
		alert(myname + "さん、こんにちは！");
		document.getElementById("myname").innerHTML = myname;
		sock.emit("myname", {value: myname});
	}

	sock.on("names", function(names){
		console.log("names recved");
		namelist = names.value.split("\n");
		for(var i = 0; i < namelist.length; ++i){
			$("#names").append("<option value='" + namelist[i]+ "'>" + namelist[i] + "</option>");
		}
	});

});

$("#names").change(function(){
	sock.emit("changename",{value: $("#names option:selected").val()});
});
