﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dms.services.preprocessing.normalization
{
    public class EnumeratedParameter : IParameter
    {
        public string Type { get { return "Enum"; } }
        public int CountNumbers
        {
            get { return countNumbers; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException();
                countNumbers = value;
            }
        }

        public EnumeratedParameter(List<string> values)
        {
            classes = new List<string>();

            foreach (string item in values)
            {
                if (!classes.Contains(item))
                    classes.Add(item);
            }
            countClasses = classes.Count;
            countNumbers = Convert.ToInt32(Math.Log10(2 * countClasses)) + 1;

            centerValue = (countClasses - 1) / 2;//(minValue + maxValue) / 2;
        }

        public int GetInt(string value)
        {
            return classes.IndexOf(value);
        }

        public float GetLinearNormalizedFloat(string value)
        {
            int val = GetInt(value);
            float step = (float) 1.0 / countClasses;
            float temp = 0.0f;
            for (int i = 0; i < countClasses; i++)
            {
                if (Math.Abs(val - temp) < 1e-10)
                {
                    return (float)(step / 2.0 + i * step);
                }
                temp++;
            }
            return float.NaN;
        }

        public float GetNonlinearNormalizedFloat(string value)
        {
            float val = GetInt(value);
            return (float)(1 / (Math.Exp(-a * (val - centerValue)) + 1));
        }

        public int GetNormalizedInt(string value)
        {
            double val = GetLinearNormalizedFloat(value);
            return Convert.ToInt32(val * Math.Pow(10, countNumbers));
        }

        public string GetFromNormalized(int value)
        {
            return GetFromLinearNormalized((float)(value / Math.Pow(10, countNumbers)));
        }

        public string GetFromLinearNormalized(float value)
        {
            float step = (float) 1.0 / (2 * countClasses);

            if (value <= 0.0)
                value = step;
            else if (value >= 1.0)
                value = 1 - step;

            value -= step;
            value = value * countClasses;
            return classes[Convert.ToInt32(value)];
        }

        public string GetFromNonlinearNormalized(float value)
        {
            if (value < 0.0f)
                value = 0.0f;
            else if (value > 1.0f)
                value = 1.0f;

            float output = (float)(centerValue - 1 / a * Math.Log(1 / value - 1));
            return Convert.ToString(output);
        }

        private float centerValue;
        private float a = 1.0f; //Параметр aвлияет на степень нелинейности изменения переменной в нормализуемом интервале.
        private readonly int countClasses;
        private int countNumbers;
        private readonly List<string> classes;
    }
}
