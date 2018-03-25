function E = Ising(par)
N=sqrt(length(par));
J=1;
if N~=floor(N)
    error('number of variable should be an squared number ( it is a 2D problem represented as a 1D vector)')
end
spin=reshape(par,N,N);
sumOfNeighbors = ...
      circshift(spin, [ 0  1]) ...
    + circshift(spin, [ 0 -1]) ...
    + circshift(spin, [ 1  0]) ...
    + circshift(spin, [-1  0]);

Em = - J * spin .* sumOfNeighbors;

E = 0.5*sum(sum(Em));
end

