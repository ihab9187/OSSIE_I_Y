x = csvread("fetch.csv");
a = x(:,1);
a = a(length(x)-99:length(x));

b = x(:,2);
b = b(length(x)-99:length(x));
plot(a); hold; plot(b,'r');

