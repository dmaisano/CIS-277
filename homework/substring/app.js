document.getElementById('output').style.visibility = 'hidden';

function fms(str) {
  str = str.split('').filter(char => char == '0' || char == '1').join('');

  return str.includes('1101') ? true : false;
}

document.getElementById('stringInput').addEventListener('input', (event) => {
  document.getElementById('output').style.visibility = 'visible';

  let userInput = event.target.value;
  let result = fms(userInput);

  result = result == 1 ? 'TRUE' : 'FALSE';

  document.getElementById('result').innerHTML = result;
  document.getElementById('result').style.textAlign = 'center';
});
