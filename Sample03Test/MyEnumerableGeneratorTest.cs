using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using Sample03Lib;

namespace Sample03Test
{
    [TestFixture]
    public class MyEnumerableGeneratorTest
    {
        [Test]
        public void CreateInstanceTest()
        {
            var meg = new MyEnumerableGenerator();
            var m = meg.CreateInstance();
            var i = 0;
            foreach (var item in m)
            {
                switch (i++)
                {
                    case 0:
                        Assert.AreEqual("aiueo", item);
                        break;
                    case 1:
                        Assert.AreEqual("kakikukeko", item);
                        break;
                    case 2:
                        Assert.AreEqual("sasisuseso", item);
                        break;
                    default:
                        Assert.Fail();
                        break;
                }
            }
            Assert.AreEqual(3, i);
        }
    }
}
