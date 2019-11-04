const backtrackedList = [
  {
    atom: "1",
    valuation: true,
    backTracked: false,
  },
  {
    atom: "2",
    valuation: true,
    backTracked: false,
  },
];

for (let i = backtrackedList.length - 1; i >= 0; i--) {
  const obj = backtrackedList[i];

  if (!obj.backTracked) {
    obj.backTracked = true;
    obj.valuation = !obj.valuation;
    break;
  }
}

console.log(backtrackedList);
