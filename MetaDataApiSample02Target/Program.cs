﻿using System;

class Program
{
    [ReplaceAttribute(0x02000003, 0x06000003)]
    static void Main(string[] args)
    {
        Console.WriteLine("Hello World!!");
    }
}

class AlternativeProgram
{
    static void Main(string[] args)
    {
        Console.WriteLine("Welcome to Low Layer World!!");
    }
}

[AttributeUsage(AttributeTargets.Method)]
sealed class ReplaceAttribute : Attribute
{
    readonly int typeDefToken;
    readonly int methodDefToken;
    public ReplaceAttribute(int typeDefToken, int methodDefToken)
    {
        this.typeDefToken = typeDefToken;
        this.methodDefToken = methodDefToken;
    }

    public int TypeDefToken { get { return typeDefToken; } }
    public int MethodDefToken { get { return methodDefToken; } }
}