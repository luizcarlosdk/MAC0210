function result = bilinear(img, h, i, j)
  function pixel = p(point)
    pixel = img(point(1), point(2));
  endfunction

  h2 = floor(h/2);
  lowerLeft = [i+h2, j-h2];
  lowerRight = [i+h2, j+h2];
  upperLeft = [i-h2, j-h2];
  upperRight = [i-h2, j+h2];

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
    + a(2) * (i - lowerLeft(1))
    + a(3) * (j - lowerLeft(2))
    + a(4) * (i - lowerLeft(1)) * (j - lowerLeft(2))
  );
endfunction
