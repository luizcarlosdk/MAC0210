function result = bilinear(img, k, h, x, y)
  function pixel = p(point)
    pixel = img(point(1), point(2));
  endfunction

  [
    lowerLeft, ...
    lowerRight, ...
    upperLeft, ...
    upperRight
  ] = getSquare(size(img)(1), k, h, x, y);

  f = [p(lowerLeft); p(lowerRight); p(upperLeft); p(upperRight)];
  m = [
    1 0 0 0
    1 0 h 0
    1 h 0 0
    1 h h h^2
  ];

  a = inv(m) * f;

  result = (
    a(1)
    + a(2) * (x - lowerLeft(1))
    + a(3) * (y - lowerLeft(2))
    + a(4) * (x - lowerLeft(1)) * (y - lowerLeft(2))
  );

endfunction

function [lowerLeft, lowerRight, upperLeft, upperRight] = getSquare(n, k, h, x, y)
  step = k + 1;
  if (x == n)
    i = n;
  else
    i = step * (max(floor(x/step), 1)) + 1;
  endif

  if (y == n)
    j = n - step;
  else
    j = step * (max(floor(y/step), 1) - 1) + 1;
  endif

  lowerLeft = [i, j];
  lowerRight = [i, j+step];
  upperLeft = [i-step, j];
  upperRight = [i-step, j+step];
endfunction
