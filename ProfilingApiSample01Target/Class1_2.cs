
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
