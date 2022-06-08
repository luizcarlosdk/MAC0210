function decompress(compressedImg, method, k, h)
  [img, colorMap] = imread(compressedImg);
  # Get RGB matrix if image has colormap.
  if (size(colorMap) > 0)
    img = 255 * ind2rgb(img, colorMap);
  endif

  n = size(img)(1);
  p = n + (n-1)*k;

  indexes = [];

  # Iterate indexes of the form i = 0 \mod{k+1}.
  for i = 1:(k+1):p
    indexes = [indexes i];
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

  for i = 1:rows(result)
    for j = 1:columns(result)
      if (isUnknownPoint(i, j, k))
        result(i,j,1) = bilinear(result(:,:,1), k, h, i, j);
        result(i,j,2) = bilinear(result(:,:,2), k, h, i, j);
        result(i,j,3) = bilinear(result(:,:,3), k, h, i, j);
      endif
    endfor
  endfor

  imwrite(uint8(result), "decompressed.png", "Quality", 100);
endfunction

function resp = isUnknownPoint(i, j, k)
  resp = mod(i - 1, k+1) != 0 || mod(j - 1, k+1) != 0;
endfunction
