// const alert

const handleSubmit = async () => {
  // fetch data
  const result = {
    data: '',
    error: true,
  };

  if (result.error) {
    const alert = document.querySelector('.alert');
    alert.setAttribute('style', 'display: grid');
    alert.classList.add('fadein');

    const alertMessage = document.querySelector('#alert--message');
    alertMessage.textContent = 'Unable to login to NJIT and Backend';

    setTimeout(() => {
      alert.classList.remove('fadein');
      alert.classList.add('fadeout');
      setTimeout(() => {
        alert.setAttribute('style', 'display: none');
        alert.classList.remove('fadeout');
      }, 1000);
    }, 6000);
  }
};
