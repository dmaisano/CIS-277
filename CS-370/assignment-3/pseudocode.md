```javascript
function gradDescent(training set T; double stepSize; double epsilon; double M) {
  initialize vectors: g_1,...,g_c arbitrarily; //exemplar points
  previousCost = infinity;
  PrevCost = infinity;
  PrevAccuracy = computeAccuracy(g_1, ..., g_c, T);

  loop {
    TotalCost = 0.0;

    for (v = 1 to c) {
      n_v = 0; // (n is a vector)
    }

    for (each datapoint Y in T) {
      v = Y.c;

      // find g_w cloest to u(Y);
      if (w != v) {
        Cost = distSquared(g_v, u(Y)) - distSquared(u(Y), g_w);

        if (Cost < M) {
          n_v += u(Y) - g_v;
          n_w += g_w - u(Y);
          TotalCost += Cost;
        } else {
          Cost += M;
        }
      }
    }

    if (TotalCost < epsilon) {
      return g_1, ..., g_c; // Training complete
    }

    if (TotalCost > (1-epsilon)*PrevCost) {
      return g_1,...,g_c; // improvement too small
    }

    for (v = 1 to c) {
      h_v = g_v + step_size * n_v;
    }

    NewAccuracy = computeAccuracy(h_1, ..., h_c, T);

    if (NewAccuracy < PrevAccuracy) {
      return g_1, ..., g_c;
    }

    for (v = 1 to c) {
      g_v = h_v;
    }

    PrevCost = TotalCost;
    PrevAccuracy = NewAccuracy;
  }
}
```
