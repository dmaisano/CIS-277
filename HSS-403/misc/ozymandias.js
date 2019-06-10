// Domenico Maisano
// HSS 403 - Summer '19

const ozymandias = {
  title: 'Ozymandias',
  description:
    '"Ozymandias" is the title of two poems published in 1818. English Romantic poet Percy Bysshe Shelley wrote a sonnet, first published in the 11 January 1818 issue of The Examiner in London.',
  lines: [
    'I met a traveller from an antique land,',
    'Who said—"Two vast and trunkless legs of stone',
    'Stand in the desert. . . . Near them, on the sand,',
    'Half sunk a shattered visage lies, whose frown,',
    'And wrinkled lip, and sneer of cold command,',
    'Tell that its sculptor well those passions read',
    'Which yet survive, stamped on these lifeless things,',
    'The hand that mocked them, and the heart that fed;',
    'And on the pedestal, these words appear:',
    'My name is Ozymandias, King of Kings;',
    'Look on my Works, ye Mighty, and despair!',
    'Nothing beside remains. Round the decay',
    'Of that colossal Wreck, boundless and bare',
    'The lone and level sands stretch far away."',
  ],
  authors: ['Percy Bysshe Shelley', 'Horace Smith'],
  datePublished: new Date(1818, 00, 11), // January 11, 1818
  isFavorite: true,
};

console.log(`Poem: ${ozymandias.title}`);

console.log(
  `Originally Published: ${ozymandias.datePublished.toLocaleDateString(
    'en-US'
  )}`
);

console.log(`Description: ${ozymandias.description}`);

console.log(`Authors: ${ozymandias.authors.join(', ')}\n`);

for (const line of ozymandias.lines) {
  console.log(line);
}
