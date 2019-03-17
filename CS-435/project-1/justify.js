str = `It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way-- in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.`;

function wordWrap(str, maxWidth) {
  var newLineStr = '\n';
  done = false;
  res = '';
  do {
    found = false;
    // Inserts new line at first whitespace of the line
    // for (i = maxWidth; i >= 0; i--) {
    //   if (testWhite(str.charAt(i))) {
    //     res += str.slice(0, i) + '\n';
    //     // res = res + [str.slice(0, i), newLineStr].join('');
    //     str = str.slice(i + 1);
    //     found = true;
    //     break;
    //   }
    // }
    // Inserts new line at maxWidth position, the word is too long to wrap
    if (!found) {
      res += [str.slice(0, maxWidth), newLineStr].join('');
      str = str.slice(maxWidth);
    }

    if (str.length < maxWidth) done = true;
  } while (!done);

  return res + str;
}

function testWhite(x) {
  var white = new RegExp(/^\s$/);
  return white.test(x.charAt(0));
}

str = wordWrap(str, 60);

console.log(str);
