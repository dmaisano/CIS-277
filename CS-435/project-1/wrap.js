function wrap(str, width = 60) {
  const newLine = '\n';

  const regex = '.{1, `${width}`}';

  const re = new RegExp(`.{1, ${width}}`, 'g');

  const lines = str.mat;
}
