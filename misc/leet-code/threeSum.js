var sortNums = (a,b) => { return a - b; }
var x = [-1, 0, 1, 2, -1, -4];
x.sort(sortNums); 

var threeSum = function(nums) {
  var triplets = [];

  for(var i = 0; i < nums.length - 2; i++) {
    var a = nums[i];
    var b = nums[i-1];

    if(i == 0 || (i > 0 && a != b)) {
      var min = i + 1;
      var max = nums.length-1; // max size of the array
      var sum = 0 - a; // x + y = 0

      while(min < max) {
        if(nums[min] + nums[max] == sum) {
          triplets.push([nums[i], nums[min], nums[max]]);

          while(min < max && nums[min] == nums[min+1]) {
            min++;
          }

          while(min < max && nums[max] == nums[max-1]) {
            max--;
          }
        }

        else if(nums[min] + nums[max] < sum) {
          min++;
        }

        else {
          max--;
        }
      }
    }
  }

  for(i in triplets) {
    console.log(triplets[i]);
  }
  
}

threeSum(x);
