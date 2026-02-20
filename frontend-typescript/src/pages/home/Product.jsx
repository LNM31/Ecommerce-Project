import { useState } from "react";
import { formatMoney } from "../../utils/money";
import axios from "axios";
import CheckmarkIcon from '../../assets/images/icons/checkmark.png';

export function Product({ product, loadCart }) 
{
  const [quantity, setQuantity] = useState(1);
  const [showAddedButton, setShowAddedButton] = useState(false);

  const addToCart = async () => 
  {
    await axios.post('/api/cart-items', {
      productId: product.id,
      quantity
    });
    await loadCart();

    setShowAddedButton(true);
    setTimeout(() => 
    {
      setShowAddedButton(false);
    }, 2000);
  }
  const selectQuantity = event => 
  {
    const quantitySelected = Number(event.target.value);
    setQuantity(quantitySelected);
  }

  return (
    <div className="product-container"
      data-testId="product-container"
    > {/* important to have a key for React */}
      <div className="product-image-container">
        <img className="product-image"
          data-testid="product-image"
          src={product.image} />
      </div>

      <div className="product-name limit-text-to-2-lines">
        {product.name}
      </div>

      <div className="product-rating-container">
        <img className="product-rating-stars"
        data-testId="product-rating-stars"
          src={`images/ratings/rating-${product.rating.stars * 10}.png`} />
        <div className="product-rating-count link-primary">
          {product.rating.count}
        </div>
      </div>

      <div className="product-price">
        {formatMoney(product.priceCents)}
      </div>

      <div className="product-quantity-container">
        <select
          data-testId="product-quantity-container"
          value={quantity}
          onChange={selectQuantity}
        >
          <option value="1">1</option>
          <option value="2">2</option>
          <option value="3">3</option>
          <option value="4">4</option>
          <option value="5">5</option>
          <option value="6">6</option>
          <option value="7">7</option>
          <option value="8">8</option>
          <option value="9">9</option>
          <option value="10">10</option>
        </select>
      </div>

      <div className="product-spacer"></div>

      <div className="added-to-cart"
        style={{opacity: showAddedButton ? 1 : 0}}
      >
        <img src={CheckmarkIcon} />
        Added
      </div>

      <button className="add-to-cart-button button-primary"
        data-testId="add-to-cart-button"
        onClick={addToCart}
      >
        Add to Cart
      </button>
    </div>
  );
}