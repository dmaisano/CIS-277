using System;
using System.Collections.Generic;
using System.Linq;

namespace knapsack
{
  class Knapsack
  {
    public List<KnapsackObject> objects { get; set; }
    public int M { get; set; } // max weight
    public int T { get; set; } // target value

    public Knapsack()
    {
      this.objects = new List<KnapsackObject>();

      this.M = 10; // default max weight
      this.T = 20; // default target value
    }

    public Knapsack(List<KnapsackObject> objects)
    {
      this.objects = new List<KnapsackObject>();

      foreach (var obj in objects)
      {
        this.addObj(obj);
      }

      this.M = 10; // default max weight
      this.T = 20; // default target value
    }

    public int totalWeight()
    {
      int res = 0;

      foreach (KnapsackObject obj in this.objects)
      {
        res += obj.Weight;
      }

      return res;
    }

    public int totalValue()
    {
      int res = 0;

      foreach (KnapsackObject obj in this.objects)
      {
        res += obj.Value;
      }

      return res;
    }

    public int Error()
    {
      return Math.Max(this.totalWeight() - this.M, 0) + Math.Max(this.T - this.totalValue(), 0);
    }

    public void addObj(KnapsackObject obj)
    {
      if (obj.Weight + this.totalWeight() <= this.M)
      {
        this.objects.Add(obj);
      }
    }

    public void removeObj(KnapsackObject obj)
    {
      if (this.objects.Count < 1) return;

      for (int i = 0; i < this.objects.Count; i++)
      {
        KnapsackObject knapsackObject = this.objects[i];

        if (knapsackObject.ID == obj.ID)
        {
          this.objects.RemoveAt(i);
        }
      }
    }

    public void printObjs()
    {
      if (this.objects.Count < 1)
      {
        System.Console.WriteLine("NO ITEMS");
        return;
      }

      for (int i = 0; i < this.objects.Count; i++)
      {
        var obj = this.objects.ElementAt(i);

        if (i == this.objects.Count - 1)
        {
          Console.Write($"{obj.ID}\n");
        }
        else
        {
          System.Console.Write($"{obj.ID}, ");
        }
      }
    }
  }

  class KnapsackObject
  {
    public string ID { get; set; }
    public int Value { get; set; }
    public int Weight { get; set; }
  }

  class Program
  {
    static void Main(string[] args)
    {
      KnapsackObject A = new KnapsackObject { ID = "A", Value = 10, Weight = 8 };
      KnapsackObject E = new KnapsackObject { ID = "E", Value = 4, Weight = 1 };

      List<KnapsackObject> objects = new List<KnapsackObject>();
      objects.Add(new KnapsackObject { ID = "B", Value = 8, Weight = 4 });
      objects.Add(new KnapsackObject { ID = "C", Value = 7, Weight = 3 });
      objects.Add(new KnapsackObject { ID = "D", Value = 6, Weight = 3 });

      List<Knapsack> states = new List<Knapsack>();
      Knapsack optimalState = new Knapsack(); // used to keep track of the most optimal state (lowest error)
      for (int i = 0; i < objects.Count; i++)
      {
        KnapsackObject obj = objects[i];
        List<KnapsackObject> tmp = new List<KnapsackObject>();
        tmp.Add(A);
        tmp.Add(E);

        Knapsack sack = new Knapsack(tmp);
        sack.addObj(obj);

        if (sack.Error() <= optimalState.Error())
        {
          optimalState = sack;
          System.Console.WriteLine("NEW OPTIMAL STATE");
          optimalState.printObjs();
          System.Console.WriteLine($"Weight: {optimalState.totalWeight()}, Value: {optimalState.totalValue()}");
        }
      }
    }
  }
}
