const char html_page[] PROGMEM = R"RawString(
<!DOCTYPE html>
<html>
  <style>
    body {font-family: sans-serif;}
    h1 {text-align: center; font-size: 30px;}
    p {text-align: center; color: #4CAF50; font-size: 40px;}
  </style>

<body>
  <h1>DS1307 Real Time Clock</h1><br>
  <p>Time - <span id="_HOUR">0</span>:<span id="_MIN">0</span>:<span id="_SEC">0</span></p>
  <p>Date - <span id="_DAY">0</span>:<span id="_MONTH">0</span>:<span id="_YEAR">0</span></p>

<script>
  setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        const text = this.responseText;
        const myArr = JSON.parse(text);
       document.getElementById("_HOUR").innerHTML = myArr[0];
        document.getElementById("_MIN").innerHTML = myArr[1];
       document.getElementById("_SEC").innerHTML = myArr[2];
       document.getElementById("_DAY").innerHTML = myArr[3];
       document.getElementById("_MONTH").innerHTML = myArr[4];
        document.getElementById("_YEAR").innerHTML = myArr[5];
      }
    };
    xhttp.open("GET", "readwebRTC", true);
    xhttp.send();
  },100);
</script>
</body>
</html>
)RawString";