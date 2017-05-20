﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dms.models
{
    public class LearningQuality : Entity
    {
        private int learnedSolverID;
        public int LearnedSolverID
        {
            get
            {
                return learnedSolverID;
            }

            set
            {
                learnedSolverID = value;
            }
        }

        private int mistakeTrain;
        public int MistakeTrain
        {
            get
            {
                return mistakeTrain;
            }

            set
            {
                mistakeTrain = value;
            }
        }

        private int mistakeTest;
        public int MistakeTest
        {
            get
            {
                return mistakeTest;
            }

            set
            {
                mistakeTest = value;
            }
        }

        private double closingError;
        public double ClosingError
        {
            get
            {
                return closingError;
            }
            set
            {
                closingError = value;
            }
        }


        public LearningQuality()
        {
            this.nameTable = "LearningQuality";
        }

        public LearningQuality(archive.ArchiveLearningQuality q)
        {
            this.nameTable = "LearningQuality";
            this.MistakeTest = q.MistakeTest;
            this.MistakeTrain = q.MistakeTrain;
            this.ClosingError = q.ClosingError;
        }

        public override Dictionary<string, string> mappingTable()
        {
            Dictionary<string, string> mappingTable = new Dictionary<string, string>();
            mappingTable.Add("LearnedSolverID", "LearnedSolverID");
            mappingTable.Add("MistakeTrain", "MistakeTrain");
            mappingTable.Add("MistakeTest", "MistakeTest");
            mappingTable.Add("ClosingError", "ClosingError");
            base.mappingTable().ToList().ForEach(x => mappingTable.Add(x.Key, x.Value));
            return mappingTable;
        }

        public static List<LearningQuality> qualitiesOfSolverId(int learntSolverId)
        {
            return LearningQuality.where(new Query("LearningQuality").addTypeQuery(TypeQuery.select)
                .addCondition("LearnedSolverID", "=", learntSolverId.ToString()), typeof(LearningQuality)).Cast<LearningQuality>().ToList();
        }
    }
}
