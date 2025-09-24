function checkWarranty(input_str) {
  const encoded_1 = [116, 104, 51, 95, 112, 51, 97, 107, 95, 48, 102, 95];
  const encoded_2 = "YzBkMW5nXw==";
  const encoded_3 = "\154\64\156\147\165\64\141\147\63\163\175";
  const decoded_1 = String.fromCharCode.apply(null, encoded_1);
  const decoded_2 = atob(encoded_2);
  const decoded_3 = encoded_3;
  const ill_give_you_this_for_free = "fallctf{jav4scr1pt_1s_";

  const final_flag = ill_give_you_this_for_free + decoded_1 + decoded_2 + decoded_3;

  return final_flag === input_str;
}