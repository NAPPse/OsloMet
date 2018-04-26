var c = document.getElementById('canvas');
var sizeb=20
canvas.width = canvas.scrollWidth;
canvas.height = canvas.scrollHeight;

var ctx = canvas.getContext('2d');


function binViewUnit(x, y, size, chujwieco, a, f) {
  ctx.beginPath();
  ctx.lineWidth = 0;
  ctx.strokeStyle = '#000';
  ctx.rect(x,y,sizeb,sizeb);
  ctx.stroke();
  ctx.fillStyle = document.getElementsByName('ledHigh')[0].value;
  if (f) {
    ctx.fill();
  }
  else{
    ctx.fillStyle = document.getElementsByName('ledLow')[0].value;
    ctx.fill();
  }

}

function isTime(a) {
  var toBinAndPad = function(d) {
      d = parseInt(d, 10).toString(2);

      while (d.length < 4) {
        d = "0" + d;
      }

      return d;
    },

    padT = function(t) {
      t = t.toString();
      return (t.length == 1) ? "0" + t : t;
    },

    D = new Date(unixTime*1000)
  hr = padT(D.getHours()),
    mn = padT(D.getMinutes()),
    se = padT(D.getSeconds()),
    document.getElementById('hr').innerHTML=hr[0]+' '+hr[1];
  document.getElementById('mn').innerHTML=mn[0]+' '+mn[1];
  document.getElementById('se').innerHTML=se[0]+' '+se[1];
  
  
    tot = toBinAndPad(hr[0]) + toBinAndPad(hr[1]) +
    toBinAndPad(mn[0]) + toBinAndPad(mn[1]) +
    toBinAndPad(se[0]) + toBinAndPad(se[1]);

  return (tot[a] == "1");
}

function drawRactangle(x, y, X, Y, scolor, bgcolor) {
  var xX = x + X,
    yY = y + Y,
    lT = function(ctx, a, b) {
      ctx.lineTo(a, b)
    },
    qC = function(ctx, a, b, c, d) {
      ctx.quadraticCurveTo(a, b, c, d)
    };

  ctx.beginPath();
  ctx.moveTo(x, y);

  lT(ctx, xX - 10, y);
  qC(ctx, xX, y, xX, y + 10);

  lT(ctx, xX, yY - 10);
  qC(ctx, xX, yY, xX - 10, yY);

  lT(ctx, x, yY);
  lT(ctx, x, y);

  //ctx.stroke();
  ctx.fillStyle = bgcolor;
  ctx.fill();
}

function drawDiffuser(){
  //ctx.fillStyle="#FFF";
  ctx.fillStyle = "rgba(255, 255, 255, 0.6)";
  ctx.fillRect(12,12,125,84);
}

function drawClock() {
  var map = {
    0: 0,
    1: 0,
    8: 0,
    16: 0
  };

  var initialX = 12;
  var initialY = 12;
  var horizontalInterval = sizeb+1;
  var verticalInteval = sizeb+1;

  var mapIndex = 0;
  for (var i = initialX; i <= horizontalInterval * 5 + initialX; i += horizontalInterval) {
    for (var j = initialY; j <= verticalInteval * 3 + initialY; j += verticalInteval) {
      if (!map[mapIndex]) {
        binViewUnit(i, j, 5, 0, mapIndex, isTime(mapIndex));
      }

      mapIndex++;
    }
  }
}



function loop() {
  ctx.clearRect(0, 0, c.width, c.height);
  
  //LINES
  ctx.beginPath();
  ctx.moveTo(0,0);
  ctx.lineTo(50,50);
  ctx.lineWidth=1;
  ctx.strokeStyle = '#333';
  ctx.stroke();
  
  ctx.beginPath();
  ctx.moveTo(0,106);
  ctx.lineTo(60,50);
  ctx.stroke();
  
  ctx.beginPath();
  ctx.moveTo(150,0);
  ctx.lineTo(130,20);
  ctx.stroke();
  
  ctx.beginPath();
  ctx.moveTo(150,106);
  ctx.lineTo(125,86);
  ctx.stroke();
  
  drawClock();
  drawDiffuser();
  setTimeout(loop, 1000);
  unixTime+=1;
}

loop();


function showValue(newValue){
  document.getElementById('range').innerHTML=(newValue*100/255).toFixed(0) + '%';
}

function switcharoo(){
	var H = document.getElementsByName('ledHigh')[0];
	var L = document.getElementsByName('ledLow')[0];
	var oH = H.value;
	var oL = L.value;
	L.value=oH;
	H.value=oL;
}

function openVis(){
  window.open('visualizer://', '_blank');
}
