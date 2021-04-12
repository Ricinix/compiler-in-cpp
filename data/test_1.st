import "test_2.st"

f2()
arr = [1,2,3]
print(arr)
arr[0] = 4
print(arr[0])
arr.removeAt(0)
print(arr)

function fff(i) {
    return i + i
}

class People {
    a = 1

    function init(i) {
        a = i
    }
    function say() {
        print(a)
    }
    function change() {
        a = a + 1
    }
}

class Student extends People {

    static b

    function init(i) {
        super(i)
    }

    function say() {
        print("from Student say")
    }

    static function staticSay() {
        print("from static ")
    }
}

i = 0

while i < 10 {
    i = i + 1
    print(fff(i))
}

sum = 0

if sum == 0 {
    print("sum is 0")
} else {
    print("sum is not 0")
}

s = new Student(i)
s.say()
Student.staticSay()

p = new People(i)
p.say()
p.change()
p.say()
