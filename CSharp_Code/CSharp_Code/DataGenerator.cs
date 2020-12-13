using System;
using System.Collections.Generic;

namespace CSharp_Code
{
    public class DataGenerator
    {
        private const int RECORD_COUNT = 10;

        public List<string> GenerateNewData()
        {
            var random = new Random();
            var listOfRecords = new List<string>();

            for (int i = 0; i < RECORD_COUNT; i++)
            {
                double angle = random.Next(0, 181);
                double distance = Math.Truncate(random.NextDouble() * 400) + 1; //Считаем в см. (Для теста положим расстояния от 1 до 11 см.
                listOfRecords.Add(distance + "; " + angle);
            }

            return listOfRecords;
        }

        public string GenerateSingleData()
        {
            var random = new Random();

            double angle = random.Next(0, 181);
            double distance = Math.Truncate(random.NextDouble() * 400) + 1;

            return distance + "; " + angle;
        }
    }
}
