using System;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine(new Class1().Print("Hello, World !!"));
        Console.WriteLine(new Class2().Print("こんにちは、世界！"));
    }
}

public class Class1
{
    public string Print(string value)
    {
        return "Hello, " + new Class2().Print(value) + " World !!";
    }
}

public class Class2
{
    public string Print(string value)
    {
        return "こんにちは、" + value + " 世界！";
    }
}
