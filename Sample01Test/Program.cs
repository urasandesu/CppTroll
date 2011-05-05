using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sample01Lib;

namespace Sample01Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var employees = new EmployeeCollection();

            var employee = default(Employee);
            employee = new Employee();
            employee.Name = "Akira Sugiura";
            employee.Id = employees.Count + 1;
            employees.Add(employee);

            employee = new Employee();
            employee.Name = "Yusuke Fujiwara";
            employee.Id = employees.Count + 1;
            employees.Add(employee);

            employee = new Employee();
            employee.Name = "Takahiro Nagao";
            employee.Id = employees.Count + 1;
            employees.Add(employee);

            foreach (IEmployee _employee in employees)
            {
                Console.WriteLine(string.Format("Employee{0:d2}: {1}", _employee.Id, _employee.Name));
            }
        }
    }
}
