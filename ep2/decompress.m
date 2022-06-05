function decompress(compressedImg, method, k, h)
  [img, colorMap] = imread(compressedImg);
  # Get RGB matrix if image has colormap.
  if (size(colorMap) > 0)
    img = 255 * ind2rgb(img, colorMap);
  endif

  n = size(img)(1);
  p = n + (n-1)*k;

  indexes = [];
  for i = 1:p
    if(mod(i - 1, k+1) == 0)
      indexes = [indexes i];
    endif
  endfor

  result = zeros(p,p,3);
  iCompressed = 1;

  for i = indexes
    jCompressed = 1;
    for j = indexes
      result(i, j,:) = img(iCompressed, jCompressed, :);
      jCompressed++;
    endfor
    iCompressed++;
  endfor

  imwrite(uint8(result), "decompressed.png", "Quality", 100);
endfunction