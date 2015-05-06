using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace Courier.Models
{
    /// <summary>
    /// Base class for all algorithms.
    /// </summary>
    public interface IAlgorithm
    {
        void Start();
        void Initialize(object ob);
        object GetResult();
    }
}
