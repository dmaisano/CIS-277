let alertIsVisible = false;

const triggerAlert = message => {
  document.querySelector('.alert').setAttribute('style', 'display: grid');
  alertIsVisible = true;

  // set the message
  document.querySelector('#alert--message').textContent = message;
  // 'Unable to login to NJIT and Backend';
};

const dismissAlert = () => {
  if (!alertIsVisible) {
    return;
  }

  document.querySelector('.alert').setAttribute('style', 'display: none');
  alertIsVisible = false;
};

const handleSubmit = async () => {
  const ucid = document.querySelector('#ucid').textContent;
  const pass = document.querySelector('#pass').textContent;

  // fetch data
  const result = fetch('http://localhost:5000/login.php', {
    method: 'POST',
    mode: 'same-origin',
    credentials: 'same-origin',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ ucid, pass }),
  });

  console.log(await result);
};
