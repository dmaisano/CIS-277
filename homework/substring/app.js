document.getElementById('output').style.visibility = 'hidden';

function fms(str) {
  str = str.split('').filter(char => char == '0' || char == '1').join('');

  return str.includes('1101') ? true : false;
}

document.getElementById('stringInput').addEventListener('input', (event) => {
  document.getElementById('output').style.visibility = 'visible';

  let userInput = event.target.value;
  let result = fms(userInput);

<<<<<<< HEAD
  if(result === true) {
    result = 'VALID SUBSTRING';
    document.getElementById('card').style.backgroundColor = '#5FB760';
  }

  else if(result === false) {
    result = 'INVALID SUBSTRING';
    document.getElementById('card').style.backgroundColor = '#D75452';
  }
=======
  result = result == 1 ? 'TRUE' : 'FALSE';
>>>>>>> 4cb5841ba5163130326f097ff50ac20642a02ef0

  document.getElementById('result').innerHTML = result;
  document.getElementById('result').style.textAlign = 'center';
});
