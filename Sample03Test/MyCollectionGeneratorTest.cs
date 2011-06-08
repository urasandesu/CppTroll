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

        [Test]
        public void CreateIntDequeCollectionTest()
        {
            var mcg = new MyCollectionGenerator();
            var idc = mcg.CreateIntDequeCollection();
            idc.Add(2);
            idc.Add(3);
            idc.Add(1);
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual(2, item);
                            break;
                        case 1:
                            Assert.AreEqual(3, item);
                            break;
                        case 2:
                            Assert.AreEqual(1, item);
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 3 but it was exceeded.");
                            break;
                    }
                }
            }

            idc.Clear();
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        default:
                            Assert.Fail("The collection's count is expected 0 but it was exceeded.");
                            break;
                    }
                }
            }

            idc.Add(5);
            idc.Add(4);
            idc.Add(6);
            {
                var item = 4;
                Assert.IsTrue(idc.Contains(item));
            }
            {
                var item = 1;
                Assert.IsFalse(idc.Contains(item));
            }

            var array = new int[4];
            idc.CopyTo(array, 1);
            Assert.AreEqual(0, array[0]);
            Assert.AreEqual(5, array[1]);
            Assert.AreEqual(4, array[2]);
            Assert.AreEqual(6, array[3]);

            idc.Remove(4);
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual(5, item);
                            break;
                        case 1:
                            Assert.AreEqual(6, item);
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 2 but it was exceeded.");
                            break;
                    }
                }
            }

            Assert.AreEqual(2, idc.Count);
            Assert.IsFalse(idc.IsReadOnly);
            Assert.AreEqual(6, idc[1]);
            try
            {
                Console.WriteLine("Item[2]: {0}", idc[2]);
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }

            idc[1] = 10;
            Assert.AreEqual(10, idc[1]);
            try
            {
                idc[2] = 20;
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }
        }

        [Test]
        public void CreateUnkVectorCollectionTest()
        {
            var mcg = new MyCollectionGenerator();
            var idc = mcg.CreateUnkVectorCollection();
            idc.Add(new A() { Value = 2 });
            idc.Add(new A() { Value = 3 });
            idc.Add(new A() { Value = 1 });
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual("2", item.ToString());
                            break;
                        case 1:
                            Assert.AreEqual("3", item.ToString());
                            break;
                        case 2:
                            Assert.AreEqual("1", item.ToString());
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 3 but it was exceeded.");
                            break;
                    }
                }
            }

            idc.Clear();
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        default:
                            Assert.Fail("The collection's count is expected 0 but it was exceeded.");
                            break;
                    }
                }
            }

            idc.Add(new A() { Value = 5 });
            var four = new A() { Value = 4 }; 
            idc.Add(four);
            idc.Add(new A() { Value = 6 });
            {
                var item = four;
                Assert.IsTrue(idc.Contains(item));
            }
            {
                var item = 1;
                Assert.IsFalse(idc.Contains(item));
            }

            var array = new A[4];
            idc.CopyTo(array, 1);
            Assert.AreEqual(null, array[0]);
            Assert.AreEqual("5", array[1].ToString());
            Assert.AreEqual("4", array[2].ToString());
            Assert.AreEqual("6", array[3].ToString());

            idc.Remove(four);
            {
                var i = 0;
                foreach (var item in idc)
                {
                    switch (i++)
                    {
                        case 0:
                            Assert.AreEqual("5", item.ToString());
                            break;
                        case 1:
                            Assert.AreEqual("6", item.ToString());
                            break;
                        default:
                            Assert.Fail("The collection's count is expected 2 but it was exceeded.");
                            break;
                    }
                }
            }

            Assert.AreEqual(2, idc.Count);
            Assert.IsFalse(idc.IsReadOnly);
            Assert.AreEqual("6", idc[1].ToString());
            try
            {
                Console.WriteLine("Item[2]: {0}", idc[2]);
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }

            idc[1] = new A() { Value = 10 };
            Assert.AreEqual("10", idc[1].ToString());
            try
            {
                idc[2] = new A() { Value = 20 };
                Assert.Fail("The throwing an exception is expected but it was not.");
            }
            catch (ArgumentException)
            {
            }
        }

        class A
        {
            public int Value { get; set; }
            public override string ToString()
            {
                return Value.ToString();
            }
        }
    }
}
