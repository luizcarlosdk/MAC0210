function result = compress(originalImg, k)
  [img, colorMap] = imread(originalImg);

  # Get RGB matrix if image has colormap.
  if (size(colorMap) > 0)
    img = 255 * ind2rgb(img, colorMap);
  endif

  result = remove_pixels(img, k)

  imwrite(uint8(result), "compressed.png", "Quality", 100);
endfunction

function result = remove_pixels(img, k)
  p = size(img)(1);
  n = floor((p + k)/(1+k));
  discardIndexes = [];

  for i = 1:p
    # Modular condition use zero-based index.
    if (mod(i - 1, k+1) != 0)
      discardIndexes = [discardIndexes i];
    endif
  endfor

  result = img(:,:,:);
  result(discardIndexes,:,:) = [];
  result(:,discardIndexes,:) = [];
endfunction
