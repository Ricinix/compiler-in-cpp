import "test_2.st"
function fff(i) {
    return i + i
}

class Student {
    a = 1
    function init(i) {
        a = i
    }
    function say() {
        print(a)
    }
}

i = 0
sum = 0

while i < 10 {
    sum = sum + i
    i = i + 1
    print(fff(i))
    s = new Student(i)
    s.say()
}
i