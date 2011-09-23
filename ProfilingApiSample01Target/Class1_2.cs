
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
        var c2 = new Hoge().Create(default(Class1));
        var ia = Hoge.IntArray();
        var imra = Hoge.IntMultiRankArray();
        return "こんにちは、" + value + " 世界！";
    }
}

public class Hoge
{
    public Class2 Create(Class1 c)
    {
        return null;
    }

    public static int[] IntArray()
    {
        return null;
    }

    public static int[,] IntMultiRankArray()
    {
        return null;
    }
}