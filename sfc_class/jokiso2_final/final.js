var talks = [];
var my_talks = [];
var names = [];
var username, myname; //相手、自分

function response(req, res) {
	var template = fs.readFileSync("final.ejs", "utf-8");
	var html = ejs.render(template, {});
	res.writeHead(200, {"Content-type": "text/html"});
	res.write(html);
	res.end();
}
var http = require("http");
var fs = require("fs");
var path = require("path");
var ejs = require("ejs");
var qs = require('querystring');
var server = http.createServer();
server.on("request", response);
server.listen(8213);
var io = require("socket.io").listen(server);
var talkpath = "./talk/talk.txt";

function read_talk(err, content){
	if(err){
		console.log("Error," + err.code);
	}else{
		talks = String(content).split("\n");
		for(var i = 0; i < talks.length; ++i){
			talks[i] = qs.parse(talks[i]);
		}
		console.log(talks);
		io.sockets.emit("talkdata",{value: talks});
	}
}

fs.readFile("./talk/talker.txt", "utf-8", function(err, name){
			//console.log(name);
			names = name.split("\n");
			console.log("array", names);
		});

io.sockets.on("connection", function(sock){

	/*sock.on("changename", function(name){
		username = name.value;
		console.log(username);
		for(var i = 0; i < talks.length; ++i){
			if(talks[i].send == myname && talks[i].recv == username){
				my_talks.push(talks[i]);
			}
		}
	});*/
	sock.on("newname", function(name){
		console.log("new_name");
		var newwhich = true;
		console.log("for start");
		for(var i = 0; i < names.length; ++i){
			console.log(names[i],name.value,names[i] == name.value);
			if(names[i] == name.value) {
				newwhich = false; 
				console.log("same_here");
				break;
			}
		}
		if(newwhich){
		fs.appendFile("./talk/talker.txt", "\n" + name.value, function(err){
			if(err) throw err;
		});
		}
		fs.readFile("./talk/talker.txt", "utf-8", function(err, name){
			console.log("newlist",name,"new_end");
			io.sockets.emit("names",{value: name});
		});
		sock.emit("newname_ok", {value: myname});

	});

	sock.on("send", function(talkobj){
		var stringdata = qs.stringify(talkobj);
		console.log(talkobj);
		fs.appendFile(talkpath, "\n" + stringdata, function(err){
			if(err) throw err;
		});
		fs.readFile(talkpath, "utf-8", read_talk);
	});

	sock.on("myname", function(myname_recv){
		console.log(myname_recv.value);
		myname == myname_recv.value;
		var talkpath = "./talk/talk.txt";
		fs.readFile("./talk/talker.txt", "utf-8", function(err, name){
			//console.log(name);
			io.sockets.emit("names",{value: name});
		});
	});

	sock.on("talk_read", function(num){
		var numarray = num.value;
		fs.readFile(talkpath, "utf-8", function(err, content){
				if(err){
					console.log("Error," + err.code);
				}else{
					talks = String(content).split("\n");
					for(var i = 0; i < talks.length; ++i){
						talks[i] = qs.parse(talks[i]);
					}
					console.log("talks",talks);
					for(var i = 0; i < numarray.length; ++i){
						talks[numarray[i]].read = true;
					}
					console.log(talks);
					var stringtalkarray = [];
					for(var n = 0; n < talks.length; ++n){
						stringtalkarray[n] = qs.stringify(talks[n]);
					}
					var stringtalk = stringtalkarray.join("\n");
					console.log(stringtalk);
					console.log(stringtalkarray);
					fs.writeFile(talkpath, stringtalk, function(err){
						console.log(err);
					})
				}
		})
	})

	sock.on("talk_req",function(bang){
		fs.readFile(talkpath, "utf-8", read_talk);
	});

});

console.log("server started on 8213.");


