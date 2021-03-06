Train1 = load("data/Train1.txt");
Train2 = load("data/Train2.txt");
Test1 = load("data/Test1.txt");
Test2 = load("data/Test2.txt");
Weight1 = load("Weight1.txt");
Weight2 = load("Weight2.txt");

x = linspace(-3,3,200);
y1 = -(Weight1(1)+x*Weight1(2))/Weight1(3);
y2 = -(Weight2(1)+x*Weight2(2))/Weight2(3);

plot(Train1(:,1),Train1(:,2),'+', Train2(:,1),Train2(:,2),'+', x, y1, '+',x, y2,'+');
xlabel("x1");
ylabel("x2");
