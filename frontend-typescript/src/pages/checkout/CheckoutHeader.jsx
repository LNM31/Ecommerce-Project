import { Link } from 'react-router';
import CheckoutLockIcon from '../../assets/images/icons/checkout-lock-icon.png';
import HomeLogo from '../../assets/images/home-logo.png';
import './CheckoutHeader.css';

export function CheckoutHeader({ cart }) 
{
  let totalQuantity = 0;
  cart.forEach(cartItem => {
    totalQuantity += cartItem.quantity;
  });

  return (
    <div className="checkout-header">
      <div className="header-content">
        <div className="checkout-header-left-section">
          <Link to="/" className="checkout-header-container">
            <img className="logo" src={HomeLogo} />
            <div className="home-text">Home</div>
          </Link>
        </div>

        <div className="checkout-header-middle-section">
          Checkout (<Link className="return-to-home-link"
            to="/">{totalQuantity} items</Link>)
        </div>

        <div className="checkout-header-right-section">
          <img src={CheckoutLockIcon} />
        </div>
      </div>
    </div>
  );
}