using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using Sample03Lib;

namespace Sample03Test
{
    [TestFixture]
    public class MyCollectionGeneratorTest
    {
        [Test]
        public void CreateStrVectorCollectionTest()
        {
            var mcg = new MyCollectionGenerator();
            var svc = mcg.CreateStrVectorCollection();
            svc.Add("tatituteto");
            svc.Add("naninuneno");
            svc.Add("hahihuheho");
            {
                var i = 0;
                foreach (var item in svc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual("tatituteto", item);
                            break;
                        case 1:
                            Assert.AreEqual("naninuneno", item);
                            break;
                        case 2:
                            Assert.AreEqual("hahihuheho", item);
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 3 but it was exceeded.");
                            break;
                    }
                }
            }

            svc.Clear();
            {
                var i = 0;
                foreach (var item in svc)
                {
                    switch (i++)
                    {
                        default:
                            Assert.Fail("The collection's count is expected 0 but it was exceeded.");
                            break;
                    }
                }
            }

            svc.Add("mamimumemo");
            svc.Add("yayuyo");
            svc.Add("rarirurero");
            {
                var item = "yayuyo";
                Assert.IsTrue(svc.Contains(item));
            }
            {
                var item = "aiueo";
                Assert.IsFalse(svc.Contains(item));
            }

            var array = new string[4];
            svc.CopyTo(array, 1);
            Assert.IsNull(array[0]);
            Assert.AreEqual("mamimumemo", array[1]);
            Assert.AreEqual("yayuyo", array[2]);
            Assert.AreEqual("rarirurero", array[3]);

            svc.Remove("yayuyo");
            {
                var i = 0;
                foreach (var item in svc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual("mamimumemo", item);
                            break;
                        case 1:
                            Assert.AreEqual("rarirurero", item);
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 2 but it was exceeded.");
                            break;
                    }
                }
            }

            Assert.AreEqual(2, svc.Count);
            Assert.IsFalse(svc.IsReadOnly);
            Assert.AreEqual("rarirurero", svc[1]);
            try
            {
                Console.WriteLine("Item[2]: {0}", svc[2]);
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }

            svc[1] = "gagigugego";
            Assert.AreEqual("gagigugego", svc[1]);
            try
            {
                svc[2] = "naninuneno";
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }
        }
    }
}
