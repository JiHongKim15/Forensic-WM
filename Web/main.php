
<?php
	require_once("tools.php");
	
	session_start_if_none();
	$id = sessionVar("uid");
	$name = sessionVar("uname");
?>



<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<!--<meta charset="utf-8">

<head>
    <title>LOGIN</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/index.css">
    <link rel="stylesheet" href="css/login.css">

  
    <style type="text/css">
        a:link { color: black; text-decoration: none;}
        a:visited { color: black; text-decoration: none;}
        a:hover { color: black; text-decoration: underline;}
    </style>

    <link href="https://fonts.googleapis.com/css?family=Nanum+Brush+Script" rel="stylesheet">
    <style>
        body
        {
            font-family: 'Nanum Brush Script', cursive;
        }
    </style>
</head>


<body>

<div id="container">
    <div id="loginer">
        <div id="form">
            <form method="post" action=<?= MEMBER_PATH?>/login.php enctype="multipart/form-data">
                <fieldset>
                    <legend>LOGIN</legend>
                    &ensp;&ensp;&ensp;ID&ensp;&ensp;&ensp;&ensp;
					<input type="text" name="id" placeholder="Enter Your Email">
                    <br><br>
                    PASSWORD&ensp;
                    <input type="password" name="pw" placeholder="Enter Your Password">
                    <br><br>
					
					<input type="submit" value="로그인">
                    <br>
                    You Don't Have Your Account?
                    <a href="signup.html"> <img src="imeages/signup.png"></a>
                </fieldset>
            </form>
        </div>
    </div>

</div>
</body>
</html>  -->


<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	</head>
	<body>
	
	<div style="position: relative;">
		<canvas id="myCanvas" width="1510" height="730" style="border:0px solid " position="relative">
		</canvas>
		
		
			<div style="font-family:'Comic Sans MS'; left: 540px; width: 450px; bottom: 300px; font-size: 1.8em; font-weight: bold; position: absolute;">
				<form method="post" action=<?= MEMBER_PATH?>/login.php enctype="multipart/form-data">
				ID&emsp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;
				<input type="text" name="id"size="30" maxlength="16" placeholder="Enter Your ID      "><br>
				PASSWORD
				<input type="password" name="pw" size="30" maxlength="16" placeholder="Enter Your Password"><br><br>
				<div style="left: 250px; width: 400px; top:100px; position: absolute;">
				<input type="image" src="enter.png" height="70" width="150" ></div>
				</form>
			</div>
		<script ="text/javascript">
			var ctx=document.getElementById("myCanvas");
			var myContext=ctx.getContext("2d");
			var text="Login";
			myContext.font="50px comic sans ms"
			myContext.color="black"
			myContext.fillText(text,510,230);
			myContext.moveTo(505,220);
			myContext.lineTo(490,220);
			myContext.lineTo(490,520);
			myContext.lineTo(990,520);
			myContext.lineTo(990,220);
			myContext.lineTo(640,220);
			myContext.stroke();
		</script>
	</div>

	</body>
</html>

