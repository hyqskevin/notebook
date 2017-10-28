## kalman filters

### tracking(跟踪)
- kalman filters：continuous(连续的)  uni-medal(单峰)
- particle filters：continous  mult-medal
- montecarlo localizaion(蒙特卡洛定位)：discrete(分离的)  multi-medal(双峰)

### Gaussian(高斯分布)
- definition:f(x) = $$\frac1{\sqrt{2*\pi*\sigma^2}}*e^{(\frac{-1}{2})*\frac{(x-\mu)^2}{\sigma^2}}$$
- uni-medal symmetrical(单峰对称)
- belief in kalman filters

```python
def f(mu, sigma2, x):
    return 1/sqrt(2.*pi*sigma2) * exp(-.5*(x-mu)**2/sigma2)
```

- shift the mean:
  - Gaussian1:$\mu,\sigma^2$|Gaussian2:$\nu,r^2$

  - $\mu*^2 = \frac{r^2\mu+\sigma^2\nu}{r^2+\sigma^2}$
  $sigma*^2 = \frac1{\frac1{r^2}+\frac1{\sigma^2}}$

  new $\mu ,\sigma $ are peaker than two gaussians

- P(x) = Gaussian1($\mu,\sigma$)
  P(z|x) = Gaussian2($\nu,r$)
  P(x|z) = Gaussian*($\mu*,\sigma*$)
